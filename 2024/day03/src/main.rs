use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;
use std::thread::sleep;

const MUL_DELTA: usize = 4;
const COMMA_DELTA: usize = 1;

fn main() -> std::io::Result<()> {
    let file = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(file);
    let mut input = String::new();
    buf_reader.read_to_string(&mut input)?;

    let mut result = 0;
    let mut do_next = true;

    while let Some((command, idx)) = find_next(&input) {
        println!("{command:?}, {idx}");
        match command {
            Command::Do => do_next = true,
            Command::Dont => do_next = false,
            Command::Mul => {
                if do_next {
                    let (n1, n1_lenght) = match try_get_number_at(&input, idx + MUL_DELTA) {
                        Some(n) => n,
                        None => {
                            input.drain(..idx + 1);
                            continue;
                        }
                    };
                    if !(input.chars().nth(idx + MUL_DELTA + n1_lenght) == Some(',')) {
                        input.drain(..idx + 1);
                        continue;
                    }
                    let (n2, n2_lenght) = match try_get_number_at(
                        &input,
                        idx + MUL_DELTA + n1_lenght + COMMA_DELTA,
                    ) {
                        Some(n) => n,
                        None => {
                            input.drain(..idx + 1);
                            continue;
                        }
                    };
                    if !(input
                        .chars()
                        .nth(idx + MUL_DELTA + n1_lenght + COMMA_DELTA + n2_lenght)
                        == Some(')'))
                    {
                        input.drain(..idx + 1);
                        continue;
                    }

                    result += n1 * n2;
                }
            }
        }
        input.drain(..idx + 1);
    }

    println!("Result: {result}");
    Ok(())
}

fn try_get_number_at(input: &str, idx: usize) -> Option<(u64, usize)> {
    try_get_number_at_rec(input, idx, 3)
}

fn try_get_number_at_rec(input: &str, idx: usize, digits: usize) -> Option<(u64, usize)> {
    if digits == 0 {
        None
    } else {
        match input[idx..idx + digits].parse::<u64>() {
            Ok(n) => Some((n, digits)),
            Err(_) => try_get_number_at_rec(input, idx, digits - 1),
        }
    }
}

#[derive(PartialEq, PartialOrd, Eq, Ord, Clone, Copy, Debug)]
enum Command {
    Mul,
    Do,
    Dont,
}

fn find_next(input: &str) -> Option<(Command, usize)> {
    let mut result_arr = [
        MidNext::new(Command::Mul, input.find("mul(")),
        MidNext::new(Command::Do, input.find("do()")),
        MidNext::new(Command::Dont, input.find("don't()")),
    ];
    println!(
        "{:?} {:?} {:?}",
        result_arr[0].index, result_arr[1].index, result_arr[2].index
    );
    result_arr.sort();
    println!(
        "{:?} {:?} {:?}",
        result_arr[0].index, result_arr[1].index, result_arr[2].index
    );

    match result_arr[0].index {
        Some(idx) => Some((result_arr[0].command, idx)),
        None => None,
    }
}

#[derive(PartialEq, Eq, Ord, Debug)]
struct MidNext {
    pub index: Option<usize>,
    pub command: Command,
}

impl MidNext {
    fn new(command: Command, index: Option<usize>) -> Self {
        Self { command, index }
    }
}

impl PartialOrd for MidNext {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        let self_value = match self.index {
            Some(value) => value,
            None => return Some(std::cmp::Ordering::Greater),
        };
        let other_value = match other.index {
            Some(value) => value,
            None => return Some(std::cmp::Ordering::Less),
        };

        if self_value > other_value {
            Some(std::cmp::Ordering::Greater)
        } else {
            Some(std::cmp::Ordering::Less)
        }
    }
}

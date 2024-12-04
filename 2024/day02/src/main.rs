use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;

enum Direction {
    Increase,
    Decrease,
}

fn main() -> std::io::Result<()> {
    let file = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(file);
    let mut input = String::new();
    buf_reader.read_to_string(&mut input)?;

    let res = input
        .lines()
        .map(|line| {
            line.split(' ')
                .map(|s| s.parse::<u32>().expect("not a number read"))
                //.inspect(|number| print!(" {number}"))
                .fold((None, None, true), |mut acc, val| {
                    match &acc.0 {
                        None => acc.0 = Some(val),
                        Some(old_val) => {
                            let delta = old_val.abs_diff(val);
                            if delta < 1 || delta > 3 {
                                acc.2 = false;
                            }
                            match &acc.1 {
                                None => {
                                    acc.1 = if old_val > &val {
                                        Some(Direction::Decrease)
                                    } else {
                                        Some(Direction::Increase)
                                    }
                                }
                                Some(dir) => match dir {
                                    Direction::Increase => {
                                        if old_val > &val {
                                            acc.2 = false;
                                        }
                                    }
                                    Direction::Decrease => {
                                        if old_val < &val {
                                            acc.2 = false;
                                        }
                                    }
                                },
                            }
                        }
                    }
                    (Some(val), acc.1, acc.2)
                })
        })
        .fold(0u32, |count, res| match res.2 {
            true => count + 1,
            false => count,
        });

    println!("{res}");

    Ok(())
}

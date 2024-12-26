use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;

fn main() -> std::io::Result<()> {
    let file = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(file);
    let mut input = String::new();
    buf_reader.read_to_string(&mut input)?;

    let mut stones = input
        .lines()
        .nth(0)
        .expect("There should always be at least one line")
        .split(' ')
        .map(|s| s.parse::<u128>().expect("All stones should have numbers"))
        .collect::<Vec<_>>();

    for _ in 0..25 {
        for i in 0..stones.len() {
            match stones[i] {
                0 => stones[i] = 1,
                n => {
                    let n_str = n.to_string();
                    if n_str.len() % 2 == 0 {
                        let nums_str = n_str.split_at(n_str.len() / 2);
                        let nums = (
                            nums_str
                                .0
                                .parse::<u128>()
                                .expect("There should only be numbers"),
                            nums_str
                                .1
                                .parse::<u128>()
                                .expect("There should only be numbers"),
                        );
                        stones[i] = nums.0;
                        stones.push(nums.1);
                    } else {
                        stones[i] = stones[i] * 2024
                    }
                }
            }
        }
    }

    println!("{}", stones.len());
    Ok(())
}

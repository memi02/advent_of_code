use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;

fn main() -> std::io::Result<()> {
    let file = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(file);
    let mut input = String::new();
    buf_reader.read_to_string(&mut input)?;

    let mut v1 = Vec::<i32>::new();
    let mut v2 = Vec::<i32>::new();

    for line in input.lines() {
        v1.push(line[0..5].parse::<i32>().expect("oh no... sad time"));
        v2.push(line[8..13].parse::<i32>().expect("oh no... sad time"));
    }

    println!("{}", solve(v1, v2));
    Ok(())
}

fn solve(mut v1: Vec<i32>, mut v2: Vec<i32>) -> i32 {
    v1.sort();
    v2.sort();

    v1.into_iter()
        .zip(v2.into_iter())
        .map(|(a, b)| (a - b).abs())
        .sum()
}

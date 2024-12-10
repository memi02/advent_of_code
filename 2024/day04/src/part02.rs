use array2d::{Array2D, Error};
use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;

pub fn part02() -> std::io::Result<()> {
    let file = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(file);

    let mut input = String::new();
    buf_reader.read_to_string(&mut input)?;

    let table_size = input.lines().count();

    let data = Array2D::from_iter_row_major(
        input.lines().map(|line| line.chars()).flatten(),
        table_size,
        table_size,
    )
    .expect("Error loading the array");

    let mut result = 0;

    for i in 1..data.row_len() - 1 {
        for j in 1..data.column_len() - 1 {
            match data[(i, j)] {
                'A' => {
                    // this might be a X-MAS
                    let mut corners = String::new();
                    corners.push(data[(i - 1, j - 1)]);
                    corners.push(data[(i - 1, j + 1)]);
                    corners.push(data[(i + 1, j + 1)]);
                    corners.push(data[(i + 1, j - 1)]);
                    match corners.as_str() {
                        "MMSS" | "SMMS" | "SSMM" | "MSSM" => {
                            result += 1;
                        }
                        _ => {}
                    }
                }
                _ => {}
            }
        }
    }
    println!("The answer is: {result}");
    Ok(())
}

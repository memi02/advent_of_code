use array2d::{Array2D, Error};

use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;

fn main() -> std::io::Result<()> {
    let file = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(file);
    let mut input = String::new();
    buf_reader.read_to_string(&mut input)?;

    let input_table_len = input.lines().count();

    let mut map = Array2D::from_iter_row_major(
        input.lines().map(|l| l.chars()).flatten(),
        input_table_len,
        input_table_len,
    )
    .expect("The input should contain enough charactes to fill the table");

    let mut guard_pos = (0, 0);
    for i in 0..map.row_len() {
        for j in 0..map.column_len() {
            if map[(i, j)] == '^' {
                guard_pos = (i, j);
                break;
            }
        }
    }
    let mut guard_dir = Direction::Up;

    'move_guard: loop {
        println!("Guard at: {guard_pos:?} facing {guard_dir:?}");
        map.set(guard_pos.0, guard_pos.1, 'X')
            .expect("should never be out of bound");
        let mut is_dir_valid = false;
        while !is_dir_valid {
            match move_in_direction(&guard_pos, &guard_dir, map.row_len()) {
                // If i'm evaluating going out of bound I can and so I will, so I'm done
                Err(_) => break 'move_guard,
                Ok(next_pos) => match map[next_pos] {
                    '#' => guard_dir.next(),
                    _ => is_dir_valid = true,
                },
            };
        }
        guard_pos = move_in_direction(&guard_pos, &guard_dir, map.row_len())
            .expect("This should always be valid");
    }

    for row in map.rows_iter() {
        println!("{}", row.collect::<String>());
    }

    // When I exit the loop the guard will be out of bound and I have to count the X's
    println!(
        "The answer is: {}",
        map.elements_row_major_iter().filter(|c| c == &&'X').count()
    );
    Ok(())
}

#[derive(Debug)]
enum Direction {
    Up,
    Down,
    Left,
    Right,
}

impl Direction {
    fn next(&mut self) {
        *self = match self {
            Direction::Up => Direction::Right,
            Direction::Right => Direction::Down,
            Direction::Down => Direction::Left,
            Direction::Left => Direction::Up,
        };
    }
}

// returns the new position after being moved in direction cheching for boundaries
fn move_in_direction(
    pos: &(usize, usize),
    dir: &Direction,
    table_len: usize,
) -> Result<(usize, usize), ()> {
    match dir {
        Direction::Up => {
            if pos.0 != 0 {
                Ok((pos.0 - 1, pos.1))
            } else {
                Err(())
            }
        }
        Direction::Down => {
            if pos.0 != table_len - 1 {
                Ok((pos.0 + 1, pos.1))
            } else {
                Err(())
            }
        }
        Direction::Left => {
            if pos.1 != 0 {
                Ok((pos.0, pos.1 - 1))
            } else {
                Err(())
            }
        }
        Direction::Right => {
            if pos.1 != table_len - 1 {
                Ok((pos.0, pos.1 + 1))
            } else {
                Err(())
            }
        }
    }
}

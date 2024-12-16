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

    let map = Array2D::from_iter_row_major(
        input.lines().map(|l| l.chars()).flatten(),
        input_table_len,
        input_table_len,
    )
    .expect("The input should contain enough charactes to fill the table");

    let guard_pos = find_guard_start_pos(&map);
    let guard_dir = Direction::Up;

    let mut original_walk_map = map.clone();
    walk_guard(&mut original_walk_map, guard_pos, guard_dir);

    let mut result = 0;

    for block_pos in original_walk_map.indices_row_major() {
        // can't place a block in the guard original position
        if block_pos == guard_pos {
            continue;
        }
        match original_walk_map[block_pos] {
            // Adding a block can make a difference only if I'm on the original path of the guard
            '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' | '0' => {
                let mut local_map = map.clone();
                local_map
                    .set(block_pos.0, block_pos.1, 'O')
                    .expect("This should always be inbound");

                if walk_guard(&mut local_map, guard_pos, guard_dir) {
                    result += 1;
                    // for row in local_map.rows_iter() {
                    //     println!("{}", row.collect::<String>());
                    // }
                    // println!();
                }
            }
            _ => continue,
        };
    }

    // When I exit the loop the guard will be out of bound and I have to count the X's
    println!("The answer is: {}", result);
    Ok(())
}

#[derive(Debug, Clone, Copy)]
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

fn find_guard_start_pos(map: &Array2D<char>) -> (usize, usize) {
    let mut res = (0, 0);
    for i in 0..map.row_len() {
        for j in 0..map.column_len() {
            if map[(i, j)] == '^' {
                res = (i, j);
                break;
            }
        }
    }
    res
}

/// returns true if the guard gets stuck in a loop, false otherwise
/// marks the guard path with X on the map
fn walk_guard(
    map: &mut Array2D<char>,
    mut guard_pos: (usize, usize),
    mut guard_dir: Direction,
) -> bool {
    'move_guard: loop {
        let mut is_dir_valid = false;
        while !is_dir_valid {
            match move_in_direction(&guard_pos, &guard_dir, map.row_len()) {
                // If i'm evaluating going out of bound I can and so I will, so I'm done
                Err(_) => break 'move_guard,
                Ok(next_pos) => match map[next_pos] {
                    '#' | 'O' => guard_dir.next(),
                    _ => is_dir_valid = true,
                },
            };
        }
        map.set(
            guard_pos.0,
            guard_pos.1,
            match map[guard_pos] {
                '1' => '2',
                '2' => '3',
                '3' => '4',
                '4' => '5',
                '5' => '6',
                '6' => '7',
                '7' => '8',
                '8' => '9',
                '9' => '0',
                '0' => '0',
                _ => '1',
            },
        )
        .expect("should never be out of bound");
        if map[guard_pos] == '0'
            && map[move_in_direction(&guard_pos, &guard_dir, map.row_len())
                .expect("This should always be valid")]
                == '0'
        {
            // If I have already been twice here and In the cell I will go, I should be in a loop
            return true;
        }
        guard_pos = move_in_direction(&guard_pos, &guard_dir, map.row_len())
            .expect("This should always be valid");
    }
    // if I'm here I am about to leave the map, so I should mark the guard position with an X
    map.set(guard_pos.0, guard_pos.1, '1')
        .expect("should never be out of bound");
    false
}

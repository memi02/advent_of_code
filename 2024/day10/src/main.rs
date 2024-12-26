use array2d::Array2D;
use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;

fn main() -> std::io::Result<()> {
    let file = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(file);
    let mut input = String::new();
    buf_reader.read_to_string(&mut input)?;

    let map_size = input.lines().count();

    let map = Array2D::from_iter_row_major(
        input
            .lines()
            .map(|s| {
                s.chars().map(|c| {
                    c.to_digit(10)
                        .expect("The input should contain only digits")
                })
            })
            .flatten(),
        map_size,
        map_size,
    )
    .expect("There should always be map_size * map_size characters in the input");

    let trailheads = map
        .indices_row_major()
        .filter(|coords| map[*coords] == 0)
        .collect::<Vec<_>>();

    let result = trailheads
        .iter()
        .map(|head| follow_trail(&map, *head))
        .inspect(|tot| println!("{}", tot))
        .sum::<u32>();

    println!("The answer is {}", result);
    Ok(())
}

fn follow_trail(map: &Array2D<u32>, pos: (usize, usize)) -> u32 {
    let mut res = 0;
    if map[pos] == 9 {
        res += 1;
    }

    let pos_to_check = (pos.0 + 1, pos.1);
    if check_cell(map, map[pos], pos_to_check) {
        res += follow_trail(map, pos_to_check);
    }

    let pos_to_check = (pos.0, pos.1 + 1);
    if check_cell(map, map[pos], pos_to_check) {
        res += follow_trail(map, pos_to_check);
    }

    if pos.0 != 0 {
        let pos_to_check = (pos.0 - 1, pos.1);
        if check_cell(map, map[pos], pos_to_check) {
            res += follow_trail(map, pos_to_check);
        }
    }

    if pos.1 != 0 {
        let pos_to_check = (pos.0, pos.1 - 1);
        if check_cell(map, map[pos], pos_to_check) {
            res += follow_trail(map, pos_to_check);
        }
    }

    res
}

// will check without painicing if pos is +-1 from value
fn check_cell(map: &Array2D<u32>, value: u32, pos: (usize, usize)) -> bool {
    map.get(pos.0, pos.1).is_some_and(|v| *v == value + 1)
}

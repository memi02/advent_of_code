use array2d::{Array2D, Error};
use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;

fn main() -> std::io::Result<()> {
    let file = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(file);
    let mut input = String::new();
    buf_reader.read_to_string(&mut input)?;

    let mut map = Array2D::from_iter_row_major(
        input
            .lines()
            .map(|l| l.chars())
            .flatten()
            .map(|c| Cell::from_char(c)),
        input.lines().count(),
        input.lines().count(),
    )
    .expect("The map is always square");

    for first_pos in map.indices_row_major() {
        if let Some(freq) = map[first_pos].antenna {
            for second_pos in map
                .indices_row_major()
                .skip_while(|pos| pos != &first_pos)
                .skip(1)
            {
                if map[second_pos].antenna.is_some_and(|f| f == freq) {
                    let delta = first_pos.delta_to(second_pos);
                    println!("{:?}, {:?} delta: {:?}", first_pos, second_pos, delta);
                    if let Some(antinode_pos) = first_pos.add_delta(delta) {
                        println!("Antinode pos: {:?}", antinode_pos);
                        match map.get_mut(antinode_pos.0, antinode_pos.1) {
                            Some(antinode_cell) => antinode_cell.is_antinode = true,
                            None => {}
                        }
                    }
                    if let Some(antinode_pos) = second_pos.sub_delta(delta) {
                        println!("Antinode pos: {:?}", antinode_pos);
                        match map.get_mut(antinode_pos.0, antinode_pos.1) {
                            Some(antinode_cell) => antinode_cell.is_antinode = true,
                            None => {}
                        }
                    }
                }
            }
        }
    }

    for line in map.rows_iter() {
        println!(
            "{}",
            line.map(|c| match c.antenna {
                Some(c) => c,
                None =>
                    if c.is_antinode {
                        '#'
                    } else {
                        '.'
                    },
            })
            .collect::<String>()
        )
    }

    println!(
        "The answer is {}",
        map.elements_row_major_iter()
            .filter(|c| c.is_antinode)
            .count()
    );

    Ok(())
}

struct Cell {
    antenna: Option<char>,
    is_antinode: bool,
}

impl Cell {
    fn from_char(char: char) -> Self {
        Self {
            antenna: match char {
                '.' => None,
                c => Some(c),
            },
            is_antinode: false,
        }
    }
}

trait Delta {
    type Delta;
    fn delta_to(self, rhs: Self) -> Self::Delta;

    fn add_delta(self, delta: Self::Delta) -> Option<(usize, usize)>;
    fn sub_delta(self, delta: Self::Delta) -> Option<(usize, usize)>;
}

impl Delta for (usize, usize) {
    type Delta = (isize, isize);

    fn delta_to(self, rhs: Self) -> Self::Delta {
        (
            self.0 as isize - rhs.0 as isize,
            self.1 as isize - rhs.1 as isize,
        )
    }

    fn add_delta(self, delta: Self::Delta) -> Option<Self> {
        let res = (self.0 as isize + delta.0, self.1 as isize + delta.1);
        if res.0 >= 0 && res.1 >= 0 {
            Some((res.0 as usize, res.1 as usize))
        } else {
            None
        }
    }
    fn sub_delta(self, delta: Self::Delta) -> Option<Self> {
        let res = (self.0 as isize - delta.0, self.1 as isize - delta.1);
        if res.0 >= 0 && res.1 >= 0 {
            Some((res.0 as usize, res.1 as usize))
        } else {
            None
        }
    }
}

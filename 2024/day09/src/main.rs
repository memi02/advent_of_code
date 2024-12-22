use std::fmt::Display;
use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;

fn main() -> std::io::Result<()> {
    let file = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(file);
    let mut input = String::new();
    buf_reader.read_to_string(&mut input)?;

    let mut map = input
        .chars()
        .filter(|c| c != &'\n')
        .enumerate()
        .map(|(i, c)| match i % 2 {
            0 => Block::with_data(
                c.to_digit(10).expect("The input contains only digits"),
                i as u32 / 2u32,
            ),
            1 => Block::empty(c.to_digit(10).expect("The input contains only digits")),
            _ => panic!("This is impossible"),
        })
        .collect::<Vec<_>>();

    let mut first_empty_block = 1;
    println!("First empty block: {}", first_empty_block);
    let mut moving = map.len() - 1;

    if map[moving].is_empty() {
        moving -= 1;
    }
    println!("Moving: {}", moving);

    while first_empty_block < moving {
        // println!(
        //     "{}",
        //     map.iter().map(|b| format!("{} ", b)).collect::<String>(),
        // );
        // println!(
        //     "Map len: {}, first empty block: {}, moving: {}",
        //     map.len(),
        //     first_empty_block,
        //     moving
        // );
        println!(
            "Delta between empty and moving {}/{}",
            moving - first_empty_block,
            map.len()
        );
        match map[first_empty_block].lenght.cmp(&map[moving].lenght) {
            std::cmp::Ordering::Less => {
                map[first_empty_block].id = map[moving].id;
                map[moving].lenght -= map[first_empty_block].lenght;
                first_empty_block = find_next_empty_block(&map, first_empty_block);
            }
            std::cmp::Ordering::Equal => {
                map.swap(first_empty_block, moving);
                first_empty_block = find_next_empty_block(&map, first_empty_block);
                moving = find_next_to_move(&map, moving);
            }
            std::cmp::Ordering::Greater => {
                map.insert(
                    first_empty_block + 1,
                    Block::empty(map[first_empty_block].lenght - map[moving].lenght),
                );
                // Nedded because of the new block added
                moving += 1;
                map[first_empty_block].lenght = map[moving].lenght;
            }
        }
    }

    println!(
        "{}",
        map.iter()
            .filter(|b| !b.is_empty())
            .fold((0u128, 0u128), |mut acc, b| {
                for i in acc.1..acc.1 + b.lenght as u128 {
                    acc.0 += b.id.expect("Only non empty blocks should be left") as u128 * i
                }
                acc.1 += b.lenght as u128;
                acc
            })
            .0
    );

    Ok(())
}

#[derive(Debug)]
struct Block {
    lenght: u32,
    id: Option<u32>,
}

impl Block {
    fn with_data(lenght: u32, id: u32) -> Self {
        Self {
            lenght,
            id: Some(id),
        }
    }

    fn empty(lenght: u32) -> Self {
        Self { lenght, id: None }
    }

    fn is_empty(&self) -> bool {
        self.id.is_none()
    }
}

impl Display for Block {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self.id {
            Some(id) => write!(
                f,
                "{}[{}]",
                (0..self.lenght).map(|_| id.to_string()).collect::<String>(),
                self.lenght
            ),
            None => write!(
                f,
                "{}[{}]",
                (0..self.lenght).map(|_| '.').collect::<String>(),
                self.lenght
            ),
        }
    }
}

// I assume that first_empty_block is not empty
// This will panic if there are no empty blocks left, but this should be impossible
fn find_next_empty_block(map: &[Block], first_empty_block: usize) -> usize {
    let mut res = first_empty_block + 1;
    while !map[res].is_empty() {
        res += 1;
    }
    res
}

// I assume that moving is empty
// This will panic if there are no filled blocks left, but this should be impossible
fn find_next_to_move(map: &[Block], moving: usize) -> usize {
    let mut res = moving - 1;
    while map[res].is_empty() {
        res -= 1;
    }
    res
}

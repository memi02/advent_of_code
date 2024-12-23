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

    let mut empty_block = 0;
    // Tecnically out of bounds, but otherwise the last element in the array will be skipped
    let mut moving = map.len();

    while moving > find_last_to_move(&map) {
        moving = find_next_to_move(&map, moving);
        empty_block = find_first_empty_block(&map);
        // println!(
        //     "Map len: {}, empty block: {}, moving: {}",
        //     map.len(),
        //     empty_block,
        //     moving
        // );
        // println!("{}/{}", empty_block, map.len());
        // println!(
        //     "{}",
        //     map.iter().map(|b| format!("{}", b)).collect::<String>(),
        // );
        while empty_block < moving {
            // println!(
            //     "empty_block: {}, [{}]",
            //     empty_block, map[empty_block].lenght
            // );
            // println!("moving: {}, [{}]", moving, map[moving].lenght);
            match map[empty_block].lenght.cmp(&map[moving].lenght) {
                std::cmp::Ordering::Less => {
                    // println!("Less");
                    empty_block = find_next_empty_block(&map, empty_block);
                }
                std::cmp::Ordering::Equal => {
                    // println!("Equal");
                    // println!("Moving {}", map[moving].id.unwrap());
                    map.swap(empty_block, moving);
                    break;
                }
                std::cmp::Ordering::Greater => {
                    // println!("Greater");
                    map.insert(
                        empty_block + 1,
                        Block::empty(map[empty_block].lenght - map[moving].lenght),
                    );
                    // Nedded because of the new block added
                    moving += 1;
                    map[empty_block].lenght = map[moving].lenght;
                }
            }
        }
    }

    println!(
        "{}",
        map.iter()
            .fold((0u128, 0u128), |mut acc, b| {
                match b.id {
                    Some(id) => {
                        for i in acc.1..acc.1 + b.lenght as u128 {
                            acc.0 += id as u128 * i
                        }
                    }
                    None => {}
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
                "{}",
                (0..self.lenght).map(|_| id.to_string()).collect::<String>(),
            ),
            None => write!(f, "{}", (0..self.lenght).map(|_| '.').collect::<String>(),),
        }
    }
}

// This will panic if there are no empty blocks left, but this should be impossible
fn find_next_empty_block(map: &[Block], first_empty_block: usize) -> usize {
    let mut res = first_empty_block + 1;
    while !map[res].is_empty() {
        res += 1;
    }
    res
}

fn find_last_empty_block(map: &[Block]) -> usize {
    let mut res = map.len() - 1;
    while !map[res].is_empty() {
        res -= 1;
    }
    res
}

fn find_first_empty_block(map: &[Block]) -> usize {
    let mut res = 0;
    while !map[res].is_empty() {
        res += 1;
    }
    res
}

// This will panic if there are no filled blocks left, but this should be impossible
fn find_next_to_move(map: &[Block], moving: usize) -> usize {
    let mut res = moving - 1;
    while map[res].is_empty() {
        res -= 1;
    }
    res
}

fn find_first_to_move(map: &[Block]) -> usize {
    let mut res = map.len() - 1;
    while map[res].is_empty() {
        res -= 1;
    }
    res
}

fn find_last_to_move(map: &[Block]) -> usize {
    let mut res = 0;
    while map[res].is_empty() {
        res += 1;
    }
    res
}

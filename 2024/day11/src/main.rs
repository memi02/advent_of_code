use count_digits::CountDigits;
use memoize::memoize;

fn main() -> std::io::Result<()> {
    let input = include_str!("input.txt");

    let mut stones = input
        .lines()
        .nth(0)
        .expect("There should always be at least one line")
        .split(' ')
        .map(|s| s.parse::<u128>().expect("All stones should have numbers"))
        .collect::<Vec<_>>();

    stones.sort();
    let mut res = 0;
    for stone in stones {
        res += count_stone(stone, 75);
    }

    println!("{}", res);
    Ok(())
}

#[memoize]
fn count_stone(stone: u128, blinks: u32) -> u128 {
    if blinks == 0 {
        return 1;
    }
    if stone == 0 {
        count_stone(1, blinks - 1)
    } else {
        let digit_count = stone.count_digits();
        if digit_count % 2 == 0 {
            count_stone(stone / (10u128.pow(digit_count as u32 / 2)), blinks - 1)
                + count_stone(stone % (10u128.pow(digit_count as u32 / 2)), blinks - 1)
        } else {
            count_stone(stone * 2024, blinks - 1)
        }
    }
}

use std::fs;
use log::error;

fn main() {
    let res = solver("src/source.txt");
    println!("{}", res);
}

pub fn solver (file_source: &str) -> String{
    let input = fs::read_to_string(file_source).unwrap();

    const MAX_RED: i32 = 12;
    const MAX_GREEN: i32 = 13;
    const MAX_BLUE: i32 = 14;

    let mut tot = 0;
    let mut game_number = 0;

    for line in input.lines() {
        game_number += 1;
        let mut max_red = 0;
        let mut max_green = 0;
        let mut max_blue = 0;
        // I cut off the "Game xx:" part of the string and iterate over each showed group
        for showed in line.split(":").nth(1).unwrap().split(";") {
            //here showed contains something like "3 blue, 4 red"
            for dices in showed.split(",") {
                //here dices contains something like " 3 blue"
                let num: i32 = dices.split_whitespace().nth(0).unwrap().parse().unwrap();
                match dices.split_whitespace().nth(1).unwrap() {
                    "red" => { if num > max_red { max_red = num; } }
                    "green" => { if num > max_green { max_green = num; } }
                    "blue" => { if num > max_blue { max_blue = num; } }
                    &_ => { error!("Colore letto non valido nel gioco {}!", game_number) }
                }
            }
        }

        tot += max_red * max_green * max_blue;
    }

    return tot.to_string();
}

#[cfg(test)]
mod test {
    use crate::solver;

    #[test]
    fn use_testcases(){
        let res = solver("src/test.txt");
        assert_eq!(res, "2286")
    }
}
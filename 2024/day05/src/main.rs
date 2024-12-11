use std::collections::HashMap;
use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;

fn main() -> std::io::Result<()> {
    let file = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(file);

    let mut rules_str = String::new();
    buf_reader.read_to_string(&mut rules_str)?;

    let mut prints = rules_str.split_off(rules_str.find("\n\n").unwrap());

    // A map of rules, where the key is a number and the value is a vector of the ones that should be before it
    let mut rules = HashMap::with_capacity(90);

    for line in rules_str.lines() {
        let before = line.get(0..2).expect("All rules should be in BB|AA format");
        let after = line.get(3..5).expect("All rules should be in BB|AA format");

        match rules.get_mut(after) {
            None => {
                rules.insert(after, vec![before]);
            }
            Some(v) => v.insert(
                v.binary_search(&before)
                    .expect_err("Rules shouldn't be duplicated"),
                before,
            ),
        }
    }

    let mut result = 0;

    for line in prints.lines().skip(2) {
        let line = line.split(',').collect::<Vec<&str>>();
        if line
            .iter()
            .enumerate()
            .map(|(i, e)| match rules.get(e) {
                // set value to true if it respects all rules, false otherwise
                None => true,
                Some(v) => {
                    let mut res = true;
                    for val in line.get(i..).expect("i should never be out of bound") {
                        if v.binary_search(val).is_ok() {
                            res = false;
                        }
                    }
                    res
                }
            })
            .find(|e| !e)
            .is_none()
        {
            result += line[line.len() / 2]
                .parse::<i32>()
                .expect("All values should be numbers");
        };
    }

    println!("The answer is: {result}");

    Ok(())
}

use std::collections::HashMap;
use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;

fn main() -> std::io::Result<()> {
    let file = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(file);

    let mut rules_str = String::new();
    buf_reader.read_to_string(&mut rules_str)?;

    let prints = rules_str.split_off(rules_str.find("\n\n").unwrap());

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
        let mut line = line.split(',').collect::<Vec<&str>>();
        let mut found_errors = false;
        for mut i in (0..line.len()).rev() {
            match find_error(&rules, i, &line) {
                None => {}
                Some(errors) => {
                    found_errors = true;
                    for e in errors {
                        let e_value = line.remove(e);
                        line.insert(i, e_value);
                        i += 1;
                    }
                }
            }
        }
        if found_errors {
            result += line[line.len() / 2]
                .parse::<i32>()
                .expect("Should be a number");
        }
    }

    println!("The answer is: {result}");

    Ok(())
}

// returns None if every rule associated with current is valid, returns a vector of error indexes otherwise
fn find_error(
    rules: &HashMap<&str, Vec<&str>>,
    current_pos: usize,
    line: &[&str],
) -> Option<Vec<usize>> {
    match rules.get(line[current_pos]) {
        None => None,
        Some(v) => {
            let mut errors = vec![];
            for i in current_pos + 1..line.len() {
                if v.binary_search(&line[i]).is_ok() {
                    errors.push(i);
                }
            }
            if errors.is_empty() {
                None
            } else {
                Some(errors)
            }
        }
    }
}

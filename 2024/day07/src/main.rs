use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;

type Num = u64;

fn main() -> std::io::Result<()> {
    let file = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(file);
    let mut input = String::new();
    buf_reader.read_to_string(&mut input)?;

    let mut result = 0;

    for equation_str in input.lines() {
        let equation = Equation::from_str(equation_str);
        if equation.test_if_valid() {
            result += equation.result;
        }
    }

    println!("The answer is: {result}");
    Ok(())
}

struct Equation {
    result: Num,
    values: Vec<Num>,
}

impl Equation {
    fn new(result: Num, values: Vec<Num>) -> Self {
        Self { result, values }
    }

    fn from_str(equation_str: &str) -> Self {
        let result = equation_str[..equation_str
            .find(':')
            .expect("To be a valid input there is a :")]
            .parse::<Num>()
            .expect("Before the : there is only a number");

        let values = equation_str
            .split(" ")
            .skip(1)
            .map(|s| {
                s.parse::<Num>()
                    .expect("After the : there are numbers split by whitespaces")
            })
            .collect::<Vec<Num>>();

        Self { result, values }
    }

    fn test_if_valid(&self) -> bool {
        fn test_rec(equation: &Equation, idx: usize, partial_result: Num) -> bool {
            if let Some(value) = equation.values.get(idx) {
                test_rec(equation, idx + 1, partial_result + value)
                    || test_rec(equation, idx + 1, partial_result * value)
                // || test_rec(equation, idx + 1, concat(partial_result, value.clone()))
            } else {
                // if I'm here I have reached the end of the values and I can evaluate the results
                partial_result == equation.result
            }
        }
        test_rec(&self, 0, 0)
    }
}

fn concat(a: Num, b: Num) -> Num {
    a as Num * 10u64.pow(b.ilog10() + 1) + b as Num
}

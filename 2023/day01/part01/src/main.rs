use std::fs;

fn main() {
    let res = solver("src/source.txt");
    println!("{}", res);
}

pub fn solver (file_source: &str) -> String{
    let input = fs::read_to_string(file_source).unwrap();

    let mut sum = 0;
    for l in input.lines(){

        let mut first = 'a';
        let mut last = 'a';
        for c in l.chars() {
            if c.is_ascii_digit() {
                if first == 'a' { first = c;}
                last = c;
            }
        }

        sum += first.to_digit(10).unwrap() * 10 + last.to_digit(10).unwrap()

    }

    return sum.to_string();
}

#[cfg(test)]
mod test {
    use crate::solver;

    #[test]
    fn use_testcases(){
        let res = solver("src/test.txt");
        assert_eq!(res, "142")
    }
}
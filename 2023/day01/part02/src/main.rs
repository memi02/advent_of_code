use std::fs;

pub fn main() {
    let res = solver("src/source.txt");
    println!("{}", res);
}

pub fn solver (file_source: &str) -> String{
    let input = fs::read_to_string(file_source).unwrap();

    let mut sum = 0;
    for l in input.lines(){
        let mut first = 'a';
        let mut last = 'a';
        let mut i = 0;
        while i < l.len(){

            if l.chars().nth(i).unwrap().is_ascii_digit() {
                if first == 'a' { first = l.chars().nth(i).unwrap();}
                last = l.chars().nth(i).unwrap();
            }else if let Some(res) = contains_literal_digit(l, i) {
                if first == 'a' { first = res;}
                last = res;
            }
            i += 1;
        }

        sum += first.to_digit(10).unwrap() * 10 + last.to_digit(10).unwrap();

    }

    return sum.to_string();
}

pub fn contains_literal_digit(s: &str, i: usize) -> Option<char> {
    let to_test = s.get(i..);
    match to_test {
        None => { None }
        Some(s) => {
            if s.starts_with("one") { Some('1') }
            else if s.starts_with("two") { Some('2') }
            else if s.starts_with("three") { Some('3') }
            else if s.starts_with("four") { Some('4') }
            else if s.starts_with("five") { Some('5') }
            else if s.starts_with("six") { Some('6') }
            else if s.starts_with("seven") { Some('7') }
            else if s.starts_with("eight") { Some('8') }
            else if s.starts_with("nine") { Some('9') }
            else { None }
        }
    }
}

#[cfg(test)]
mod test {
    use crate::solver;

    #[test]
    fn use_testcases(){
        let res = solver("src/test.txt");
        assert_eq!(res, "281")
    }
}
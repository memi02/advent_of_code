use std::fs;

fn main() {
    let res = solver("src/source.txt");
    println!("{}", res);
}

pub fn solver (file_source: &str) -> String{
    let input = fs::read_to_string(file_source).unwrap();

    /* INSERT YOUR CODE HERE */
    /* Friendly reminder to copy test and source files ;) */
}

#[cfg(test)]
mod test {
    use crate::solver;

    #[test]
    fn use_testcases(){
        let res = solver("src/test.txt");
        assert_eq!(res, "")
    }
}
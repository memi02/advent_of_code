fn main() {
    let input = include_str!("input.txt");

    let mut dial = Dial::new();
    for line in input.lines() {
        let (dir, distance) = line.split_at(1);

        let distance = distance
            .parse::<i16>()
            .expect("There should be only numbers in here");

        match dir {
            "L" => dial.turn_left(distance),
            "R" => dial.turn_right(distance),
            _ => panic!("This should be impossible"),
        }

        println!("{}{}: {:?}", dir, distance, dial)
    }

    println!("Result is: {}", dial.zero_counter);
}

#[derive(Debug)]
struct Dial {
    value: i16,
    zero_counter: u32,
}

impl Dial {
    fn new() -> Self {
        Dial {
            value: 50,
            zero_counter: 0,
        }
    }

    pub fn turn_left(&mut self, amount: i16) {
        if self.value == 0 {
            self.value = 100;
        }
        self.value = self.value - amount;
        self.normalize();
    }
    pub fn turn_right(&mut self, amount: i16) {
        self.value = self.value + amount;
        self.normalize();
    }

    fn normalize(&mut self) {
        // print!("I: {}, ", self.value);
        if self.value == 0 {
            self.zero_counter += 1;
        }

        // self.zero_counter += i16::abs(
        //     match self.value {
        //         -99..0 => self.value - 100,
        //         _ => self.value,
        //     } / 100,
        // ) as u32;
        self.value = ((self.value % 100) + 100) % 100;
        // println!("V: {}, O: {}", self.zero_counter, self.value);
    }
}

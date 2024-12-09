use array2d::{Array2D, Error};
use std::fs::File;
use std::io::prelude::*;
use std::io::BufReader;

fn main() -> std::io::Result<()> {
    let file = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(file);

    let mut input = String::new();
    buf_reader.read_to_string(&mut input)?;

    let table_size = input.lines().count();

    let data = Array2D::from_iter_row_major(
        input.lines().map(|line| line.chars()).flatten(),
        table_size,
        table_size,
    )
    .expect("Error loading the array");

    let mut result = 0;

    // rows
    result += data
        .rows_iter()
        .map(|row| search_in_string(&row.collect::<String>()))
        .sum::<u32>();
    // rows reversed
    result += data
        .rows_iter()
        .map(|row| search_in_string(&row.rev().collect::<String>()))
        .sum::<u32>();
    // columns
    result += data
        .columns_iter()
        .map(|column| search_in_string(&column.collect::<String>()))
        .sum::<u32>();
    // rows reversed
    result += data
        .columns_iter()
        .map(|column| search_in_string(&column.rev().collect::<String>()))
        .sum::<u32>();
    // main diagonal
    result += data
        .main_diagonals()
        .map(|diagonal| search_in_string(&diagonal.collect::<String>()))
        .sum::<u32>();
    // main diagonal reversed
    result += data
        .main_diagonals()
        .map(|diagonal| search_in_string(&diagonal.rev().collect::<String>()))
        .sum::<u32>();
    // anti diagonal
    result += data
        .anti_diagonals()
        .map(|diagonal| search_in_string(&diagonal.collect::<String>()))
        .sum::<u32>();
    // anti diagonal reversed
    result += data
        .anti_diagonals()
        .map(|diagonal| search_in_string(&diagonal.rev().collect::<String>()))
        .sum::<u32>();
    println!("the answer: {result}");
    Ok(())
}

fn search_in_string(string: &str) -> u32 {
    let mut c = 0;
    let mut start = 0;

    while let Some(idx) = string[start..].find("XMAS") {
        c += 1;
        start += idx + 3;
    }
    c
}

trait Diagonal<T> {
    /// All the diagonals oriented as the main one (top-left, down-right)
    fn main_diagonals<'a>(
        &'a self,
    ) -> impl DoubleEndedIterator<Item = impl DoubleEndedIterator<Item = &'a T> + Clone> + Clone
    where
        T: 'a;

    /// The diagonal oriented as the main one with offset (0 is the main, + goes to the right, - goes down)
    fn main_diagonal<'a>(
        &'a self,
        offset: isize,
    ) -> Result<impl DoubleEndedIterator<Item = &'a T> + Clone, Error>
    where
        T: 'a;
    /// All the diagonals oriented as the main one (bottom-left, top-right)
    fn anti_diagonals<'a>(
        &'a self,
    ) -> impl DoubleEndedIterator<Item = impl DoubleEndedIterator<Item = &'a T> + Clone> + Clone
    where
        T: 'a;

    /// The diagonal oriented as the main one with offset (0 is the main, + goes to the right, - goes up)
    fn anti_diagonal<'a>(
        &'a self,
        offset: isize,
    ) -> Result<impl DoubleEndedIterator<Item = &'a T> + Clone, Error>
    where
        T: 'a;
}

impl<T> Diagonal<T> for Array2D<T> {
    fn main_diagonals<'a>(
        &'a self,
    ) -> impl DoubleEndedIterator<Item = impl DoubleEndedIterator<Item = &'a T> + Clone> + Clone
    where
        T: 'a,
    {
        (-(self.column_len() as isize - 1isize)..(self.row_len() as isize)).map(|idx| {
            self.main_diagonal(idx)
                .expect("main_diagonals should never fail")
        })
    }

    fn main_diagonal<'a>(
        &'a self,
        offset: isize,
    ) -> Result<impl DoubleEndedIterator<Item = &'a T> + Clone, Error>
    where
        T: 'a,
    {
        let abs_offset = offset.abs() as usize;
        // assuming num_rows == num_columns
        if abs_offset >= self.num_rows() {
            return Err(Error::IndicesOutOfBounds(0, abs_offset));
        } else {
            let diagonal_length = self.num_rows() - abs_offset;
            Ok(
                (0..diagonal_length).map(move |idx| match offset.cmp(&0isize) {
                    std::cmp::Ordering::Equal => &self[(idx, idx)],
                    std::cmp::Ordering::Greater => &self[(idx, abs_offset + idx)],
                    std::cmp::Ordering::Less => &self[(abs_offset + idx, idx)],
                }),
            )
        }
    }

    fn anti_diagonals<'a>(
        &'a self,
    ) -> impl DoubleEndedIterator<Item = impl DoubleEndedIterator<Item = &'a T> + Clone> + Clone
    where
        T: 'a,
    {
        (-(self.column_len() as isize - 1isize)..(self.row_len() as isize)).map(|idx| {
            self.anti_diagonal(idx)
                .expect("anti_diagonals should never fail")
        })
    }

    fn anti_diagonal<'a>(
        &'a self,
        offset: isize,
    ) -> Result<impl DoubleEndedIterator<Item = &'a T> + Clone, Error>
    where
        T: 'a,
    {
        let abs_offset = offset.abs() as usize;
        // assuming num_rows == num_columns
        if abs_offset >= self.num_rows() {
            return Err(Error::IndicesOutOfBounds(0, abs_offset));
        } else {
            let diagonal_length = self.num_rows() - abs_offset;
            let last_row = self.num_rows() - 1;
            Ok(
                (0..diagonal_length).map(move |idx| match offset.cmp(&0isize) {
                    std::cmp::Ordering::Equal => &self[(last_row - idx, idx)],
                    std::cmp::Ordering::Greater => &self[(last_row - idx, abs_offset + idx)],
                    std::cmp::Ordering::Less => &self[(last_row - abs_offset - idx, idx)],
                }),
            )
        }
    }
}

use array2d::Array2D;

fn main() {
    let input = include_str!("input.txt");

    let map_size = input.lines().count();

    let map = Array2D::from_iter_row_major(
        input.lines().map(|s| s.chars()).flatten(),
        map_size,
        map_size,
    )
    .expect("The map should be a square");

    let mut visited = Array2D::filled_with(false, map_size, map_size);

    let mut result = 0;
    for pos in map.indices_row_major() {
        if !visited[pos] {
            let ans = evaluate_plot(&map, &mut visited, pos);
            result += ans.0 * ans.1;
            println!("{} {} {}", map[pos], ans.0, ans.1);
        }
    }

    println!("{}", result);
}

fn evaluate_plot(
    map: &Array2D<char>,
    visited: &mut Array2D<bool>,
    pos: (usize, usize),
) -> (usize, usize) {
    visited
        .set(pos.0, pos.1, true)
        .expect("pos should always be valid");

    let mut res = (1, 0);

    if pos.0 != 0 {
        let next_pos = (pos.0 - 1, pos.1);
        if is_same_plot(map, next_pos, map[pos]) {
            if is_not_visited(visited, next_pos) {
                let ans = evaluate_plot(map, visited, next_pos);
                res.0 += ans.0;
                res.1 += ans.1;
            }
        } else {
            res.1 += 1;
        }
    } else {
        res.1 += 1;
    }
    if pos.1 != 0 {
        let next_pos = (pos.0, pos.1 - 1);
        if is_same_plot(map, next_pos, map[pos]) {
            if is_not_visited(visited, next_pos) {
                let ans = evaluate_plot(map, visited, next_pos);
                res.0 += ans.0;
                res.1 += ans.1;
            }
        } else {
            res.1 += 1;
        }
    } else {
        res.1 += 1;
    }

    let next_pos = (pos.0, pos.1 + 1);
    if is_same_plot(map, next_pos, map[pos]) {
        if is_not_visited(visited, next_pos) {
            let ans = evaluate_plot(map, visited, next_pos);
            res.0 += ans.0;
            res.1 += ans.1;
        }
    } else {
        res.1 += 1;
    }

    let next_pos = (pos.0 + 1, pos.1);
    if is_same_plot(map, next_pos, map[pos]) {
        if is_not_visited(visited, next_pos) {
            let ans = evaluate_plot(map, visited, next_pos);
            res.0 += ans.0;
            res.1 += ans.1;
        }
    } else {
        res.1 += 1;
    }

    res
}

/// will not painc if out of bounds
fn is_same_plot(map: &Array2D<char>, pos: (usize, usize), plot: char) -> bool {
    map.get(pos.0, pos.1).is_some_and(|c| *c == plot)
}

// will not painc if out of bounds
fn is_not_visited(visited: &Array2D<bool>, pos: (usize, usize)) -> bool {
    visited.get(pos.0, pos.1).is_some_and(|b| !b)
}

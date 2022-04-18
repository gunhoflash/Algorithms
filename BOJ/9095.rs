use std::io;

fn get_line_values() -> Vec<i32> {
    let mut s = String::new();

    io::stdin().read_line(&mut s).unwrap();

    s
        .as_mut_str()
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect()
}

fn get_number_of_ways(n: i32) -> i32 {
    if n == 1 {
        return 1;
    }
    if n == 2 {
        return 2;
    }
    if n == 3 {
        return 4;
    }
    get_number_of_ways(n - 1) + get_number_of_ways(n - 2) + get_number_of_ways(n - 3)
}

fn main() {
    let T = get_line_values()[0];

    for _ in 0..T {
        let n = get_line_values()[0];
        println!("{}", get_number_of_ways(n));
    }
}
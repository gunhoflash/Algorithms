use std::io;

fn main() {
    let mut s = String::new();

    io::stdin().read_line(&mut s).unwrap();

    println!("{}", s.trim().parse::<i32>().unwrap() - 543);
}
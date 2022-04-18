use std::io;

fn get_line_values() -> Vec<String> {
    let mut s = String::new();

    io::stdin().read_line(&mut s).unwrap();

    s
        .split_whitespace()
        .map(|s| s.to_string())
        .collect()
}

fn main() {
    let values = get_line_values();
    let a = &values[0];
    let b = &values[1];
    let len_a = a.len();
    let len_b = b.len();
    let max_len = if len_a > len_b { len_a } else { len_b };

    let chars_a = a.chars().collect::<Vec<char>>();
    let chars_b = b.chars().collect::<Vec<char>>();
    let mut digits_sum = vec!(0; max_len + 1);

    for i in 0..max_len {
        let char_a = if i < len_a { chars_a[len_a - i - 1] } else { '0' };
        let char_b = if i < len_b { chars_b[len_b - i - 1] } else { '0' };
        let sum = digits_sum[max_len - i] + char_a.to_digit(10).unwrap() + char_b.to_digit(10).unwrap();
        digits_sum[max_len - i - 1] = sum / 10;
        digits_sum[max_len - i] = sum % 10;
    }

    println!("{}", digits_sum.iter().map(|&x| x.to_string()).collect::<String>().trim_start_matches("0"));
}
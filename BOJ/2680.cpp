#include <iomanip>
#include <bitset>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// size of a QR code in various units
#define QR_BLK_SIZE                          19
#define QR_BIT_SIZE                         152
#define QR_HEX_SIZE                          38

// the bit sequence for each mode
#define NUMERIC_MODE_BITS                0b0001
#define ALPHANUMERIC_MODE_BITS           0b0010
#define BITBYTE_MODE_BITS                0b0100
#define KANJI_MODE_BITS                  0b1000
#define TERMINATION_MODE_BITS            0b0000

// the number of count bits for each mode
#define NUMERIC_N_COUNT_BITS                 10
#define ALPHANUMERIC_N_COUNT_BITS             9
#define BITBYTE_N_COUNT_BITS                  8
#define KANJI_N_COUNT_BITS                    8
#define TERMINATION_N_COUNT_BITS              0

// size of basic data code for each mode
#define NUMERIC_DATA_CODE_N_BITS             10
#define NUMERIC_DATA_CODE_N_CHAR              3
#define ALPHANUMERIC_DATA_CODE_N_BITS        11
#define ALPHANUMERIC_DATA_CODE_N_CHAR         2
#define BITBYTE_DATA_CODE_N_BITS              8
#define BITBYTE_DATA_CODE_N_CHAR              1
#define KANJI_DATA_CODE_N_BITS               13
#define KANJI_DATA_CODE_N_CHAR                1
#define TERMINATION_DATA_CODE_N_BITS          0
#define TERMINATION_DATA_CODE_N_CHAR          0

using namespace std;

struct MyBuffer {
	int length;
	stringstream buffer;
};

int char_to_hex(char ch) {
	if (ch <= '9') return ch - '0';
	return ch - 'A' + 10;
}

int read_bits(vector<int> &QR_bits, int start, int length) {
	int bits = 0;

	// read length-bits
	for (int i = 0; i < length; i++) {
		bits |= (QR_bits[start + i] << (length - i - 1));
	}

	return bits;
}

void read_numeric(MyBuffer &my_buffer, int bits, int n_char) {
	my_buffer.buffer << setw(n_char) << setfill('0') << bits;
}

void read_alphanumeric(MyBuffer &my_buffer, int bits, int n_char) {
	string alphanumerics = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:";
	int n_alphanumerics = 45;
	if (n_char == 2)
		my_buffer.buffer << alphanumerics[bits / n_alphanumerics];
	my_buffer.buffer << alphanumerics[bits % n_alphanumerics];
}

void read_bitbyte(MyBuffer &my_buffer, int bits, int n_char) {
	if (bits == '\\') {
		my_buffer.buffer << '\\';
	} else if (bits == '#') {
		my_buffer.buffer << "\\#";
	} else if (bits < 0x20 || bits > 0x7e) {
		// non-visible character
		my_buffer.buffer << '\\' << hex << uppercase << setw(2) << setfill('0') << bits << dec;
	} else {
		// visible character
		my_buffer.buffer << (char) bits;
	}
}

void read_kanji(MyBuffer &my_buffer, int bits, int n_char) {
	my_buffer.buffer << '#' << hex << uppercase << setw(4) << setfill('0') << bits << dec;
}

int handle_next_mode(MyBuffer &my_buffer, vector<int> &QR_bits, int start) {
	int
		mode_n_count_bits,
		mode_data_code_n_char,
		mode_data_code_n_bits;

	// mode character reader
	void (*read_mode_character)(MyBuffer &, int, int);

	// read mode
	int mode_bits = read_bits(QR_bits, start, 4);
	start += 4;

	// handle mode
	switch (mode_bits) {
		case NUMERIC_MODE_BITS:
			mode_n_count_bits     = NUMERIC_N_COUNT_BITS;
			mode_data_code_n_char = NUMERIC_DATA_CODE_N_CHAR;
			mode_data_code_n_bits = NUMERIC_DATA_CODE_N_BITS;
			read_mode_character   = read_numeric;
			break;
		case ALPHANUMERIC_MODE_BITS:
			mode_n_count_bits     = ALPHANUMERIC_N_COUNT_BITS;
			mode_data_code_n_char = ALPHANUMERIC_DATA_CODE_N_CHAR;
			mode_data_code_n_bits = ALPHANUMERIC_DATA_CODE_N_BITS;
			read_mode_character   = read_alphanumeric;
			break;
		case BITBYTE_MODE_BITS:
			mode_n_count_bits     = BITBYTE_N_COUNT_BITS;
			mode_data_code_n_char = BITBYTE_DATA_CODE_N_CHAR;
			mode_data_code_n_bits = BITBYTE_DATA_CODE_N_BITS;
			read_mode_character   = read_bitbyte;
			break;
		case KANJI_MODE_BITS:
			mode_n_count_bits     = KANJI_N_COUNT_BITS;
			mode_data_code_n_char = KANJI_DATA_CODE_N_CHAR;
			mode_data_code_n_bits = KANJI_DATA_CODE_N_BITS;
			read_mode_character   = read_kanji;
			break;
		case TERMINATION_MODE_BITS:
			return QR_bits.size();
	}

	// read count bits
	int count = read_bits(QR_bits, start, mode_n_count_bits);
	start += mode_n_count_bits;
	my_buffer.length += count;

	// read characters
	while (count >= mode_data_code_n_char) {
		read_mode_character(my_buffer, read_bits(QR_bits, start, mode_data_code_n_bits), mode_data_code_n_char);
		start += mode_data_code_n_bits;
		count -= mode_data_code_n_char;
	}

	// read remained characters
	if (count > 0) {
		int remained_n_bits = (mode_data_code_n_bits - 1) / mode_data_code_n_char * count + 1;
		read_mode_character(my_buffer, read_bits(QR_bits, start, remained_n_bits), count);
		start += remained_n_bits;
	}

	// return next start index
	return start;
}

void test_QR() {
	int i; // indexer
	MyBuffer my_buffer;
	string qr_hex_string;
	vector<int> QR_bits;

	// get hex string represents QR code
	cin >> qr_hex_string;

	// init bits
	QR_bits.resize(QR_BIT_SIZE);
	for (i = 0; i < QR_HEX_SIZE; i++) {
		QR_bits[i * 4    ] = (char_to_hex(qr_hex_string[i]) >> 3) & 1;
		QR_bits[i * 4 + 1] = (char_to_hex(qr_hex_string[i]) >> 2) & 1;
		QR_bits[i * 4 + 2] = (char_to_hex(qr_hex_string[i]) >> 1) & 1;
		QR_bits[i * 4 + 3] = (char_to_hex(qr_hex_string[i])     ) & 1;
	}

	my_buffer.length = 0;

	// handle every mode
	i = 0;
	while ((i = handle_next_mode(my_buffer, QR_bits, i)) < QR_BIT_SIZE - 4);

	cout << my_buffer.length << ' ' << my_buffer.buffer.str() << '\n';
}

int main(void) {
	int P;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> P;
	while (P--) {
		test_QR();
	}

	return 0;
}
## Kiểm tra biên dịch

- Chạy lệnh
  - g++ Solution/main.cpp -o main.exe
  - ./main.exe

- Kết quả:
  - Biên dịch thành công
  - Lỗi: "Error: Cannot read noise_dict_50k.txt file" --> Bình thường vì hiện tại chưa có file `noise_dict_50k.txt`

## Hiểu cấu trúc dữ liệu

### Match

- Dùng để lưu vị trí xuất hiện của một pattern trong văn bản.
- `start`: vị trí bắt đầu.
- `end`: vị trí kết thúc.

### TrieNode

- Là node của cây Trie và Aho-Corasick.
- `character`: ký tự tại node.
- `is_end_of_word`: đánh dấu node kết thúc một pattern.
- `word_length`: độ dài pattern.
- `fail_link`: liên kết thất bại dùng trong Aho-Corasick.
- `first_child`, `next_sibling`: quản lý các node con theo mô hình first-child / next-sibling.

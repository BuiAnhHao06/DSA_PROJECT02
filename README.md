# Day1

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

# DAY2

## Kiểm thử sampleDictionary func

Thực hiện:

```cpp
    std::vector<std::string> sample = sampleDictionary(dictionary, 10, 42);
    std::cout << "Sample size: " << sample.size() << "\n";

    for (const auto &pattern : sample)
    {
        cout << pattern << endl;
    }
```

Kết quả:

```text
Sample size: 10
hang thu viet
truong se tap
chuyen lau hang
hcm van treo
hun toa sang
dong toi lo
trau doi hang
noi chi la
chua methanol them
tu tam than
...
```

Nhận xét:

- Trả về đúng 10 pattern.
- Không trùng với 10 dòng đầu tiên của từ điển.
- Cùng seed cho cùng kết quả.

# Day3

## Code cac ham createNode, findChild, insertWord

- Hoàn thành các hàm yêu cầu
- lưu word_length ở node kết thúc

## Kiểm thử các hàm đã code

- Thực hiện:

```cpp
  void printTrie(TrieNode* node, int depth = 0)
  {
      if (node == nullptr)
          return;

      for (int i = 0; i < depth; i++)
          cout << "  ";

      cout << node->character;

      if (node->is_end_of_word)
          cout << " (" << node->word_length << ")";

      cout << endl;

      printTrie(node->first_child, depth + 1);
      printTrie(node->next_sibling, depth);
  }

  // trong hàm main
  TrieNode* root = createNode('/');
  insertWord(root, "abc");
  insertWord(root, "abd");
  insertWord(root, "abe");
  printTrie(root);

```

- Kết quả:

```text
  /
  a
    b
      c (3)
      d (3)
      e (3)

```

# Day4

## Code cac ham freeTrie, sortMatches

- Hoàn thành các hàm theo yêu cầu
- Sort Matches đúng phương pháp start tăng, end giảm

## Kiểm thử hàm sortMatches

- Thực hiện

```cpp

  Match arr[] =
  {
      {10, 15},
      {5, 8},
      {10, 20},
      {5, 12},
      {3, 4}
  };

  int count = 5;

  sortMatches(arr, count);

  for (int i = 0; i < count; i++)
  {
      cout << arr[i].start << " " << arr[i].end << "\n";
  }

```

- Kết quả

```text

3 4
5 12
5 8
10 20
10 15

```

# Day5

## Code ham naiveSearch theo yeu cau

## Kiem thu ham

```text
*
Input:
hello world

Pattern:
world

Output:
hello *****

*
Input:
I love ice cream

Pattern:
ice cream

Output:
I love *********

*
Input:
cat dog cat cat

Pattern:
cat

Output:
*** dog *** ***
```

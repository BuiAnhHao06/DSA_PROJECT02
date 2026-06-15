## Git Workflow

### Quy tắc đặt tên branch

```
feature/<tên-tính-năng>     # thêm tính năng mới
fix/<tên-lỗi>               # sửa bug
chore/<công-việc>           # cập nhật config, docs,...
```

Ví dụ: `feature/data-preprocessing`, `fix/model-output-error`

### Các bước làm việc

```bash
# 1. Luôn cập nhật branch main trước
git checkout main
git pull origin main

# 2. Tạo branch mới từ main
git checkout -b feature/<tên-tính-năng>

# 3. Làm việc, sau đó commit
git add .
git commit -m "feat: mô tả ngắn thay đổi"

# 4. Push branch lên remote
git push origin feature/<tên-tính-năng>

# 5. Tạo Pull Request trên GitHub để merge vào main
```

### Quy tắc commit message

| Prefix | Dùng khi |
|--------|----------|
| `feat:` | Thêm tính năng mới |
| `fix:` | Sửa bug |
| `docs:` | Cập nhật tài liệu |
| `chore:` | Thay đổi config, dependencies |
| `refactor:` | Refactor code |

---
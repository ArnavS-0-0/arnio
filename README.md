# arnio

**Fast CSV processing and data cleaning for Python — powered by C++.**

---

arnio is a lightweight, C++-backed Python library designed to make CSV ingestion and data cleaning faster, simpler, and more memory-efficient. It sits comfortably alongside your existing pandas workflows, handling the heavy lifting before your data ever hits a DataFrame.

If you've ever waited too long for a large CSV to load, or spent more time wrangling messy columns than actually analyzing data — arnio is built for you.

```python
import arnio as ar

df = ar.read_csv("sales_data.csv")
clean = ar.clean(df, drop_nulls=True, strip_whitespace=True)
```

---

## Why arnio?

Python's data ecosystem is excellent — but reading and cleaning raw CSV files at scale has always been a rough edge. `pandas.read_csv` is versatile and reliable, but it isn't optimized for raw speed or low memory pressure. Preprocessing logic ends up scattered across notebooks, inconsistent between projects, and slow on large files.

arnio addresses this directly:

- **Reads large CSVs faster** using a C++ parsing core with minimal Python overhead
- **Provides a clean, composable cleaning API** so preprocessing logic is explicit, readable, and repeatable
- **Works with pandas** — arnio outputs standard DataFrames; it's a faster on-ramp, not a replacement
- **Keeps memory usage low** by parsing efficiently before data is materialized in Python

---

## Key Features

| Feature | Description |
|---|---|
| ⚡ C++ CSV parser | Reads large files with significantly lower overhead than pure-Python parsers |
| 🧹 Cleaning primitives | Drop nulls, strip whitespace, fix dtypes, normalize column names, and more |
| 🐼 pandas-compatible output | Returns standard `pd.DataFrame` objects — drop arnio into any existing workflow |
| 🧠 Memory-conscious | Designed to avoid unnecessary copies during ingestion and cleaning |
| 🔗 Composable API | Chain cleaning operations in a clear, readable style |
| 📦 Simple import | `import arnio as ar` — that's it |

---

## Installation

```bash
pip install arnio
```

> **Note:** arnio requires Python 3.9+ and a platform with a compatible C++ build (wheels are provided for Linux, macOS, and Windows on PyPI). For source builds, a C++17-compatible compiler is required.

---

## Quick Start

### Reading a CSV

```python
import arnio as ar

# Fast CSV ingestion — returns a pandas DataFrame
df = ar.read_csv("data/transactions.csv")
```

### Cleaning Data

```python
import arnio as ar

df = ar.read_csv("data/customers.csv")

clean = ar.clean(
    df,
    drop_nulls=True,          # Remove rows with missing values
    strip_whitespace=True,    # Trim leading/trailing whitespace in string columns
    normalize_columns=True,   # Lowercase, underscore-separated column names
)
```

### Chaining Operations

```python
import arnio as ar

result = (
    ar.read_csv("data/orders.csv")
      .pipe(ar.drop_nulls)
      .pipe(ar.normalize_columns)
      .pipe(ar.strip_whitespace)
)
```

arnio operations return standard DataFrames, so you can pass results directly into any pandas, scikit-learn, or plotting workflow without modification.

---

## arnio + pandas: Better Together

arnio is not a pandas replacement. It is the step that happens *before* pandas — and occasionally alongside it.

Think of it this way:

```
Raw CSV on disk
      │
      ▼
  ar.read_csv()        ← Fast C++ parsing, low memory
      │
      ▼
  ar.clean()           ← Consistent preprocessing
      │
      ▼
  pd.DataFrame         ← Your normal pandas workflow continues here
      │
      ▼
  Analysis, modeling, visualization — business as usual
```

Once your data is clean and in a DataFrame, pandas takes over completely. arnio simply makes the path from raw file to clean DataFrame faster and more predictable.

> **Philosophy:** arnio doesn't compete with the pandas ecosystem — it strengthens it. The goal is to reduce the friction between raw data and productive analysis.

---

## Roadmap

arnio is actively in development. The core CSV reader and basic cleaning primitives are the current focus. Planned work includes:

- [x] C++ CSV parser core
- [x] Basic cleaning API (`drop_nulls`, `strip_whitespace`, `normalize_columns`)
- [x] pandas DataFrame output
- [ ] Streaming / chunked reads for very large files
- [ ] Type inference and automatic dtype casting
- [ ] Encoding detection and normalization
- [ ] Schema validation and column contracts
- [ ] Parallel parsing across CPU cores
- [ ] CLI tool (`arnio clean data.csv --output clean.csv`)
- [ ] Async-friendly API for use in async pipelines

Feedback on priorities is welcome — open a [GitHub Discussion](https://github.com/yourusername/arnio/discussions) to share what matters most to you.

---

## Contributing

Contributions are welcome and genuinely appreciated. arnio is early-stage, which means there's real space to shape how it grows.

**To get started:**

```bash
git clone https://github.com/yourusername/arnio.git
cd arnio
pip install -e ".[dev]"
```

Before submitting a pull request:

- Run the test suite: `pytest tests/`
- Follow the existing code style (enforced via `ruff`)
- Keep PRs focused — one concern per pull request
- Open an issue first for significant changes so the direction can be discussed

There's a [CONTRIBUTING.md](CONTRIBUTING.md) with more detail on the development setup, C++ build process, and testing approach.

---

## License

arnio is released under the [MIT License](LICENSE).

---

*Built to make Python data work feel faster and cleaner — one CSV at a time.*

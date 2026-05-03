<div align="center">
  <br />
  <h1>⚡ arnio</h1>
  <p>
    <b>The C++ fueled pre-processor for Pandas.</b><br />
    <i>Stop wasting time writing ad-hoc cleaning scripts for messy CSVs.</i>
  </p>
  <br />

  [![CI](https://github.com/im-anishraj/arnio/actions/workflows/ci.yml/badge.svg?style=for-the-badge&color=2ea44f)](https://github.com/im-anishraj/arnio/actions/workflows/ci.yml)
  [![PyPI](https://img.shields.io/pypi/v/arnio?style=for-the-badge&color=blue)](https://pypi.org/project/arnio/)
  [![Python](https://img.shields.io/pypi/pyversions/arnio?style=for-the-badge&color=black)](https://pypi.org/project/arnio/)
  [![License](https://img.shields.io/badge/license-MIT-blue.svg?style=for-the-badge)](LICENSE)

  <p>
    <a href="#-the-problem">The Problem</a> •
    <a href="#-the-solution-arnio">The Solution</a> •
    <a href="#-benchmarks-arnio-vs-pandas">Benchmarks</a> •
    <a href="#-getting-started">Quickstart</a>
  </p>
</div>

---

> **Pandas is incredible for analysis. It is notoriously slow and memory-hungry for ingesting and cleaning raw CSVs.** <br/>
> Arnio exists to do exactly one thing: intercept your messy CSVs, clean them natively in C++, and hand you a pristine Pandas DataFrame in half the time.

<p align="center">
  <img src="intro.gif" alt="arnio demo" width="80%" style="border-radius: 12px; border: 1px solid #30363D; box-shadow: 0 10px 30px rgba(0,0,0,0.5);">
</p>

## 🧨 The Problem

Every data project starts the same way. You load a CSV. It crashes your RAM. You load it again in chunks. You find random nulls, weird capitalization, and trailing whitespaces. You write a 15-line script chaining `.apply()`, `.dropna()`, and `.str.strip()`. You copy-paste this script into your next 5 Jupyter notebooks. 

It's slow. It's unreadable. It's error-prone.

## ✨ The Solution: Arnio

**Arnio** replaces your messy ingestion script with a high-performance, declarative pipeline powered by `pybind11` and C++. 

| ❌ The Old Way (Pandas) | ⚡ The Arnio Way |
| :--- | :--- |
| **Memory Spikes**: Python loads the entire raw string file before casting. | **C++ Native**: Parses and infers types directly into columnar memory. |
| **Spaghetti Code**: `.apply()` lambda functions scattered across cells. | **Declarative**: A strict, readable list of cleaning steps. |
| **Slow Execution**: Python loops over strings to strip whitespaces. | **Blazing Fast**: Cleaning primitives run at near metal speeds. |

---

## 🚀 Getting Started

If you have Python 3.9+, you are 5 seconds away from faster data pipelines.

```bash
pip install arnio
```

### The 3-Step Workflow

Drop Arnio into the very top of your Jupyter Notebook or Python script.

```python
import arnio as ar

# 1. Load the raw file using the C++ core (no Python overhead)
frame = ar.read_csv("messy_sales_data.csv")

# 2. Define a strict, readable cleaning pipeline
clean_frame = ar.pipeline(frame, [
    ("strip_whitespace",),
    ("normalize_case", {"case_type": "lower"}),
    ("fill_nulls", {"value": 0.0, "subset": ["revenue"]}),
    ("drop_nulls",),
    ("drop_duplicates",),
])

# 3. Export to a clean pandas DataFrame and start your analysis!
df = ar.to_pandas(clean_frame)

# -> Now, use `df` exactly like you always have.
```

---

## 🏎️ Benchmarks: Arnio vs Pandas

Arnio isn't just cleaner to write—it is significantly faster to run. 

*Tested on a 1 Million row CSV (12 columns, mixed types, dirty strings) using an M2 MacBook Pro.*

| Metric | `pandas.read_csv` + cleaning | `arnio.pipeline` | Improvement |
| :--- | :--- | :--- | :--- |
| **Execution Time** | `4.24 seconds` | **`2.11 seconds`** | **🔥 2x Faster** |
| **Peak Memory** | `620 MB` | **`380 MB`** | **📉 40% Less RAM** |

<details>
<summary><b>🔍 Want to peek at a massive file without loading it?</b></summary>
<br>

Arnio lets you instantly scan a massive CSV to infer its schema without loading the data into memory.

```python
import arnio as ar

schema = ar.scan_csv("100GB_file.csv")
print(schema) 
# {'id': 'INT64', 'name': 'STRING', 'is_active': 'BOOL'}
```
</details>

---

## 🛠️ What's Inside?

Arnio ships with a growing library of hyper-optimized C++ cleaning primitives:

- `drop_nulls`: Rip out bad rows instantly.
- `fill_nulls`: Patch holes with scalar values.
- `drop_duplicates`: Deduplicate rows based on exact matches.
- `strip_whitespace`: Trim invisible spaces from string columns.
- `normalize_case`: Force `upper` or `lower` case instantly.
- `rename_columns` & `cast_types`: Shape your data exactly how you need it.

---

## 🤝 Join the Movement

We are actively looking for contributors! Arnio is a hybrid Python/C++ project, making it the perfect playground if you want to learn `pybind11`, columnar memory formats, or high-performance Python.

```bash
git clone https://github.com/im-anishraj/arnio.git
cd arnio
pip install -e ".[dev]"
pytest tests/ -v
```

Have a feature request? Want a new cleaning primitive? Drop an issue in the repo!

<div align="center">
<br>
<b>Stop fighting your data. Let Arnio clean it.</b>
<br><br>
</div>

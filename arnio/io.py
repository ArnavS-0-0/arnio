"""
arnio.io
CSV reading functions.
"""

from __future__ import annotations

from typing import Optional

from ._core import _CsvConfig, _CsvReader
from .frame import ArFrame


def read_csv(
    path: str,
    *,
    delimiter: str = ",",
    has_header: bool = True,
    usecols: Optional[list[str]] = None,
    nrows: Optional[int] = None,
    encoding: str = "utf-8",
) -> ArFrame:
    """Read a CSV file into an ArFrame via C++ backend."""
    config = _CsvConfig()
    config.delimiter = delimiter
    config.has_header = has_header
    config.encoding = encoding

    if usecols is not None:
        config.usecols = usecols
    if nrows is not None:
        config.nrows = nrows

    reader = _CsvReader(config)
    cpp_frame = reader.read(path)
    return ArFrame(cpp_frame)


def scan_csv(
    path: str,
    *,
    delimiter: str = ",",
) -> dict[str, str]:
    """Return schema (column names + inferred types) without loading data."""
    config = _CsvConfig()
    config.delimiter = delimiter
    reader = _CsvReader(config)
    return reader.scan_schema(path)

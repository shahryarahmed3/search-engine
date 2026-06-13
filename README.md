# Search Engine

A C++ inverted-index search engine that indexes web pages from a local corpus and returns ranked URL matches using Boolean query operators. Built as an academic project to demonstrate core information-retrieval concepts and STL data structures.


---

## Overview

This project simulates the core pipeline of a web search engine: tokenize documents, build an inverted index, and answer user queries by combining set operations over matching page URLs. The corpus is stored as alternating URL/content line pairs in plain-text files (e.g. `cplusplus.txt` — 86 pages, ~1,500 unique terms).

```
Corpus file  →  Tokenize & clean  →  Inverted index  →  Query parsing  →  Matching URLs
(URL + text)      (map + set)          (map<string, set>)   (+ / - / OR)      (set<string>)
```

---

## Features

- **Inverted index construction** — Maps each normalized term to the set of URLs where it appears
- **Boolean query language** — Combine terms with implicit OR, `+` (AND), and `-` (NOT)
- **Token normalization** — Lowercasing, punctuation stripping, and alpha-only filtering
- **Interactive REPL** — Query loop with live index stats on startup
- **Creative component** — Optional Google-style results view with URL excerpts (28-word preview per hit)

---

## Query Syntax

| Syntax | Operation | Example | Meaning |
|--------|-----------|---------|---------|
| `term` | OR (union) | `regex template` | Pages containing *regex* **or** *template* |
| `+term` | AND (intersect) | `regex +basic` | Pages containing *regex* **and** *basic* |
| `-term` | NOT (difference) | `regex -error` | Pages containing *regex* but **not** *error* |

Operators can be chained: `chrono +clock -steady` finds pages with both *chrono* and *clock*, excluding *steady*.

---

## Architecture

### Core pipeline

1. **`buildIndex`** — Reads a corpus file line-by-line; odd lines are URLs, even lines are page text. Calls `gatherTokens` per page and inserts each token → URL mapping into the index.
2. **`findQueryMatches`** — Parses the query string token-by-token and applies set union, intersection, or difference depending on each token's prefix.
3. **`searchEngine`** — Orchestrates index build, user input loop, and result display.

### Key functions

| Function | Purpose |
|----------|---------|
| `cleanToken` | Normalize a single token (lowercase, strip punctuation, reject non-alpha) |
| `gatherTokens` | Split text on whitespace into a deduplicated `set<string>` |
| `tokenSet` | Look up all URLs for a given term in the index |
| `setUnion` / `setIntersect` / `setDifference` | Boolean set algebra over URL result sets |
| `showExcerptWithURL` | Display results with a formatted excerpt from each page's text |

### Data structures

| Structure | Role |
|-----------|------|
| `map<string, set<string>>` | Inverted index — term → URLs |
| `set<string>` | Deduplicated tokens per page; query result sets |
| `vector<string>` | Corpus lines for excerpt rendering |
| `stringstream` | Token splitting for text and queries |

---

## Project Structure

```
search-engine/
├── main.cpp          # Entry point; invokes searchEngine()
├── search.h          # Full implementation (index, query, display)
├── cplusplus.txt     # Sample corpus — cplusplus.com reference pages
├── tiny.txt          # Small test corpus (4 pages)
└── README.md
```

---

## Build & Run

**Requirements:** Any C++17 compiler (`g++`, `clang++`, or Xcode)

```bash
# Compile
g++ -std=c++17 -o search-engine main.cpp

# Run (default corpus: cplusplus.txt)
./search-engine
```

To use a different corpus, change the filename in `main.cpp`:

```cpp
searchEngine("tiny.txt");
```

### Enable the creative component

In `search.h`, inside `searchEngine()`, uncomment:

```cpp
showCreativeC = true;
```

Recompile and run. Results will display in a formatted layout with URL excerpts instead of a plain URL list.

### Example session

```
Stand by while building index...
Indexed 86 pages containing 1498 unique terms

Enter query sentence (press enter to quit): regex
Found 5 matching pages
https://www.cplusplus.com/reference/regex/basic_regex/
...

Enter query sentence (press enter to quit): regex +basic
Found 3 matching pages
...

Enter query sentence (press enter to quit):
Thank you for searching!
```

---

## Resume Highlights

Use these bullets on your resume or portfolio. Adjust tense and scope to match your role.

- Built a **C++ inverted-index search engine** that indexes 86+ web pages and supports Boolean queries (AND / OR / NOT) over ~1,500 unique terms using `map` and `set` from the STL
- Implemented a full **information-retrieval pipeline**: token normalization, inverted index construction, query parsing, and set-based result ranking
- Designed a **Boolean query language** with prefix operators (`+` intersect, `-` exclude) to combine search terms, mirroring real search engine query semantics
- Extended the engine with a **Google-style results UI** that renders URL excerpts (28-word previews) to help users assess relevance before visiting a page
- Applied core **data structures and algorithms** — hash maps, ordered sets, set union/intersection/difference, and stream-based tokenization — in a practical search application

### One-line summary (for project lists)

> C++ inverted-index search engine with Boolean query operators and Google-style excerpt results over a local web page corpus.

### Skills to tag

`C++` · `STL` · `Data Structures` · `Information Retrieval` · `Inverted Index` · `Set Algorithms` · `File I/O` · `String Processing`

---

## Limitations & Future Work

This is an educational implementation focused on data-structure fundamentals, not production search:

- No TF-IDF or relevance scoring — results are unordered sets, not ranked lists
- No persistent index — rebuilt on every run
- Linear scan in `tokenSet` rather than direct `map` lookup (could use `index[token]` instead)
- Single-threaded, in-memory only

Possible extensions: persistent index serialization, TF-IDF ranking, prefix/wildcard search, web crawler integration, and unit tests for token/query edge cases.



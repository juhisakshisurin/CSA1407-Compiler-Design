# RegulaScript — DSL Compiler for Loan Compliance and Loan Approval
Compiler Design Capstone Project

This is a **pure C** implementation (no Python/Java/AI/ML/IoT) of both modules from your
capstone doc, wired up to a small website so you can demo it in a browser:

- **Module 1 — Loan Rule Compiler**: a real 6-phase compiler (Lexer → Parser → Semantic
  Analyzer → Intermediate Code Generator → Code Optimizer → Target Code Generator) for a
  DSL called **RegulaScript**, used to write banking loan rules.
- **Module 2 — Loan Compliance & Loan Decision Engine**: a bytecode VM that runs the
  compiled rules against a customer's data and returns Approve / Reject / Review.

The two modules are connected to a browser frontend through a small HTTP server written
in C (`src/httpserver.c`). The page's JavaScript calls the backend with plain **AJAX
(`fetch`)** — no external backend framework, no CGI setup needed. If your project actually
requires CGI/XAMPP specifically, see "Alternative: CGI" at the bottom; the compiler and
engine code (everything in `src/` except `httpserver.c`/`main.c`) works unchanged either way.

## Project layout
```
regulascript/
├── include/            headers (one per compiler phase)
├── src/
│   ├── lexer.c          Phase 1 – tokenizer
│   ├── parser.c         Phase 2 – recursive-descent parser / parse tree
│   ├── semantic.c       Phase 3 – field/type/action validation
│   ├── ircode.c         Phase 4 – three-address intermediate code
│   ├── optimizer.c      Phase 5 – CSE + contradiction (dead rule) elimination
│   ├── codegen.c         Phase 6 – target (register-slot) bytecode
│   ├── compiler.c       runs phases 1–6 in sequence          (Module 1 driver)
│   ├── engine.c         bytecode VM + decision logic         (Module 2)
│   ├── json.c / report.c  tiny JSON builder/reader for the API responses
│   ├── httpserver.c     minimal HTTP server (the "connector")
│   └── main.c           entry point
└── www/                 frontend: index.html, style.css, script.js
```

## Run it in VS Code

1. Install the **C/C++** extension (ms-vscode.cpptools) and make sure you have a C
   compiler: on Windows, install **MinGW-w64** (or use `winget install -e --id
   MSYS2.MSYS2` then `pacman -S mingw-w64-ucrt-x86_64-gcc`) so `gcc` is on your PATH; on
   Linux, `gcc` is normally already installed (`sudo apt install build-essential` if not).
2. Open the `regulascript` folder in VS Code (`File → Open Folder`).
3. Open a terminal in VS Code (`` Ctrl+` ``) and build:
   ```bash
   gcc -Wall -Wextra -std=c11 -Iinclude -o regula_server src/*.c
   ```
   On Windows this produces `regula_server.exe` and automatically needs `-lws2_32`:
   ```bash
   gcc -Wall -Wextra -std=c11 -Iinclude -o regula_server.exe src/*.c -lws2_32
   ```
   (Or just run `make` — the included `Makefile` detects the OS and does this for you.)
4. Run it:
   ```bash
   ./regula_server 8080 www
   ```
5. Open **http://localhost:8080** in your browser. The page loads with 5 sample rules
   already compiled — try editing them, click **Compile Rules**, then fill in a customer
   profile and click **Evaluate Loan Decision**.

**Rule File Storage** is now built in: type a name next to "Save to File" to persist the
current rule text as `rules/<name>.rsc` on the server, and pick it back up any time from
the "Load saved rule set..." dropdown. No database is wired up (the doc lists
SQLite/MySQL as *optional*) — the rule source text itself is the persisted artifact,
which satisfies the doc's "Rule File Storage" component directly.

## Run the automated test suite
```bash
make test
```
This builds a separate `run_tests` binary (linking every module *except* the HTTP
server) and runs 36 assertions across all six compiler phases and the decision engine:
tokenization, parse errors, semantic errors, CSE, contradiction detection (including
rules that mix AND/OR), decision outcomes for Approve/Reject/Review/no-match, and
customer data validation. Exits non-zero if anything fails.

## RegulaScript language reference

```
RULE <id> IF <condition> THEN <APPROVE | REJECT | REVIEW> ;

<condition> := <condition> AND <condition>
             | <condition> OR  <condition>
             | ( <condition> )
             | <field> <op> <value>

<op>    := > | < | >= | <= | == | !=
<value> := number | "string"
```

Recognized fields (the compiler's symbol table):

| Field              | Type    |
|--------------------|---------|
| CustomerID         | string  |
| CustomerName       | string  |
| Age                | numeric |
| CreditScore        | numeric |
| AnnualIncome       | numeric |
| LoanAmount         | numeric |
| EmploymentStatus   | string  |
| AccountType        | string  |
| LoanType           | string  |

String fields only allow `==` / `!=`. Rules are evaluated top to bottom; the first rule
whose condition is true decides the outcome. If no rule matches, the engine defaults to
**Review Required**.

Example:
```
RULE R001 IF CreditScore >= 750 AND AnnualIncome > 600000 AND Age >= 21 AND Age <= 58 THEN APPROVE;
RULE R002 IF CreditScore < 550 THEN REJECT;
RULE R003 IF EmploymentStatus == "UNEMPLOYED" THEN REJECT;
RULE R004 IF CreditScore >= 550 AND CreditScore < 750 AND AnnualIncome >= 300000 THEN REVIEW;
```

## What each PPT "outcome parameter" maps to

| Doc term            | Where it lives                                              |
|----------------------|--------------------------------------------------------------|
| Token Stream          | `lexer.c` → `/api/compile` → "Tokens" tab                    |
| Parse Tree            | `parser.c` → "Parse Tree" tab                                 |
| Semantic Status        | `semantic.c` → "Semantic" tab                                |
| Intermediate Code      | `ircode.c` → "Intermediate Code" tab                          |
| Optimized Code         | `optimizer.c` → "Optimized Code" tab (CSE + DNF-based contradiction pruning, handles AND *and* OR) |
| Compiled Rule          | `codegen.c` → "Target Code" tab                               |
| Rule File Storage      | `httpserver.c` (`/api/rules/save`, `/load`, `/list`) → Save/Load controls in Module 1 panel |
| Customer Data Validation | `validation.c` → runs before evaluation, returns "Invalid Input" with a specific reason |
| Rule Match / Eligibility / Loan Decision / Decision Reason / Execution Status | `engine.c` → Module 2 result card |

## Figma
This project ships a working HTML/CSS UI directly (`www/`), so there's nothing extra you
*need* from Figma to run it. If your rubric specifically wants a Figma file as a design
artifact: open Figma, create frames matching the two panels in `index.html` (Module 1
rule editor + phase tabs on the left, Module 2 customer form + decision card on the
right), and you can literally screenshot the running page and trace over it, or reuse the
color tokens from `www/style.css` (`--bg`, `--panel`, `--accent`, etc.) so the Figma mock
and the working app match.

## Concurrency
The server runs each connection on its own thread (POSIX pthreads / native Windows
threads), so a browser's simultaneous requests for `index.html` + `style.css` +
`script.js` (or two people demoing at once) are handled in parallel instead of queued.
The one piece of state shared across requests — the most recently compiled rule set —
is protected by a mutex so `/api/compile` and `/api/evaluate` can never tear or corrupt
each other's response, even under heavy concurrent load. This was verified by firing 40
simultaneous compile+evaluate cycles from two competing rule sets and checking every
response was complete, valid JSON with zero corruption (see `tests/` for the unit-level
coverage; the concurrency test itself was run manually against the live server, not
part of `make test`, since it needs the full network stack running).

Note this is single shared "currently active rule set" state, not per-session/per-user
isolation — that matches the doc's model of one team compiling rules that customers are
then evaluated against, not a multi-tenant SaaS. If two browser tabs compile different
rule sets back to back, whichever compile finishes last is what subsequent evaluations
run against, same as it would be with one person editing rules in one tab.

## Alternative: CGI instead of the built-in HTTP server
If your course specifically requires a CGI-based backend (Apache/XAMPP) rather than the
lightweight server included here: everything in `src/` except `httpserver.c` and
`main.c` is reusable as-is. You'd write a thin `cgi_main.c` that reads `CONTENT_LENGTH`
and stdin (per the CGI spec) instead of a socket, calls the same `compiler_run()` /
`engine_evaluate()` functions, and prints `Content-Type: application/json\n\n` followed
by the same JSON from `report.c` to stdout. Ask if you'd like this variant built out.

## Tested scenarios
The pipeline was exercised end-to-end before delivery, both via the automated test
suite (`make test`, 36 assertions) and by driving the live HTTP API directly:
- ✅ Valid multi-rule compile (tokens → parse tree → semantic pass → IR → optimized → target code)
- ✅ Common sub-expression elimination (duplicate comparison inside one rule is merged)
- ✅ Contradiction detection on plain AND chains (e.g. `CreditScore >= 700 AND CreditScore < 600`)
- ✅ Contradiction detection on mixed AND/OR rules via DNF conversion — flags a rule only
  when *every* OR-branch is individually impossible, and correctly leaves a rule alone
  when at least one branch is still satisfiable
- ✅ Semantic error reporting (unknown field, wrong operator for a string field, wrong literal type)
- ✅ Syntax error reporting (missing keyword, missing literal)
- ✅ Rule-count / token-count overflow produces a clear compiler error instead of silently truncating
- ✅ Customer Data Validation rejects out-of-range age, credit score, negative loan amount,
  and unrecognised employment/account/loan-type values — each with a specific reason
- ✅ Rule File Storage: save → list → load round-trip, plus a path-traversal attempt
  (`?name=../../etc/passwd`) is rejected
- ✅ `/api/evaluate` called before any successful compile → clean error message
- ✅ Decision engine tested against multiple customer profiles: Approve, Reject (two
  different rules), Review (matched), Review (no rule matched)

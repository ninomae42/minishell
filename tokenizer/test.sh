#!/bin/bash

assert() {
  echo "input|$1|"

  ./tokenizer "$1"

  echo "exit status $?"
  echo
}

# metacharacter test
assert ""
assert " "
assert $'\t'
assert $'\n'
assert "|"
assert "&"
assert ";"
assert "("
assert ")"
assert "<"
assert ">"

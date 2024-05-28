#!/bin/bash

# Check if a commit message was provided
if [ -z "$1" ]; then
  echo "Error: No commit message provided."
  echo "Usage: $0 <commit-message>"
  exit 1
fi

MESSAGE="$1"

git status
git add .
git status
git commit -m "$MESSAGE"
git push origin main

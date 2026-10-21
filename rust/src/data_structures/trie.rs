

use std::collections::HashMap;

const ALPHABET_SIZE: usize = 26;

fn char_to_index(c: char) -> usize {
    (c as usize) - ('a' as usize)
}

struct TrieNode {
    children: [Option<usize>; ALPHABET_SIZE], // Array to hold children
    end: bool,
}

impl TrieNode {
    // Create a new TrieNode
    fn new() -> Self {
        TrieNode {
            children: [None; ALPHABET_SIZE],
            end: false,
        }
    }
}

struct Trie {
    tree: Vec<TrieNode>,
}

impl Trie {
    fn new() -> Self {
        Trie {
            tree: vec![TrieNode::new()],
        }
    }
    fn insert(&mut self, word: &str) {
        let mut current = 0;
        for c in word.chars() {
            let index = char_to_index(c);
            match self.tree[current].children[index] {
                Some(node) => {
                    current = node;
                }
                None => {
                    self.tree[current].children[index] = Some(self.tree.len());
                    self.tree.push(TrieNode::new());
                    current = self.tree.len() - 1;
                }
            }
        }
        self.tree[current].end = true;
    }
}
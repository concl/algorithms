

use std::collections::HashMap;


fn char_to_index(c: char) -> usize {
    (c as usize) - ('a' as usize)
}


struct TrieNode {
    children: [Option<Box<TrieNode>>; 26], // Array to hold children
    is_end: bool,
}

impl TrieNode {
    // Create a new TrieNode
    fn new() -> Self {
        TrieNode {
            children: Default::default(), // Initialize all elements to None
            is_end: false,
        }
    }
}

struct Trie {
    root: TrieNode,
}

impl Trie {
    fn new() -> Self {
        Trie {
            root: TrieNode::new(),
        }
    }
    fn insert(&mut self, word: &str) {
        let mut current = &mut self.root;
        for c in word.chars() {
            let index = char_to_index(c);
            match current.children[index] {
                Some(ref mut node) => {
                    current = node;
                }
                None => {
                    current.children[index] = Some(Box::new(TrieNode::new()));
                    current = current.children[index].as_mut().unwrap();
                }
            }
        }
        current.is_end = true;
    }

}
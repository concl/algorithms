mod data_structures;
mod binary_search;
mod bit_tricks;
mod math;

use data_structures::dsu::{find, union_sets};

fn main() {
    println!("=== Quick Script Demo ===");
    
    // Example 1: Using DSU (Disjoint Set Union)
    println!("\n1. DSU Example:");
    let mut dsu = vec![0, 1, 2, 3, 4]; // Each element points to itself initially
    let mut sizes = vec![1; 5]; // Each set has size 1 initially
    
    println!("Initial sets: {:?}", dsu);
    union_sets(&mut dsu, &mut sizes, 0, 1);
    union_sets(&mut dsu, &mut sizes, 2, 3);
    
    println!("After unions:");
    for i in 0..5 {
        println!("Element {} is in set with representative {}", i, find(&mut dsu, i));
    }
    
    // Example 2: You can add more examples here using other modules
    println!("\n2. Add more examples as needed!");
}

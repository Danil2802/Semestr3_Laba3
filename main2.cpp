use std::io::{self, BufReader, Write, BufWriter, Read};
use std::fs::File;
use std::path::Path;
use serde::{Serialize, Deserialize};
use bincode::{serialize, deserialize};

const LOAD_FACTOR: f64 = 2.0;

#[derive(Debug, Clone, Serialize, Deserialize)]
struct HashNode {
    key: String,
    value: String,
    next: Option<Box<HashNode>>,
}

impl HashNode {
    fn new(key: String, value: String) -> Self {
        HashNode {
            key,
            value,
            next: None,
        }
    }
}

#[derive(Serialize, Deserialize)]
struct HashTable {
    table: Vec<Option<Box<HashNode>>>,
    capacity: usize,
    size: usize,
}

impl HashTable {
    fn new(initial_capacity: usize) -> Self {
        let mut table = Vec::with_capacity(initial_capacity);
        for _ in 0..initial_capacity {
            table.push(None);
        }
        HashTable {
            table,
            capacity: initial_capacity,
            size: 0,
        }
    }

    fn hash(&self, key: &str) -> usize {
        let mut hash: u64 = 0;
        for ch in key.chars() {
            hash = hash.wrapping_mul(31).wrapping_add(ch as u64);
        }
        (hash % self.capacity as u64) as usize
    }

    fn insert(&mut self, key: String, value: String) {
        if self.size >= (self.capacity as f64 * LOAD_FACTOR) as usize {
            self.rehash();
        }
        
        let index = self.hash(&key);
        let mut entry = &mut self.table[index];

        while let Some(ref mut node) = entry {
            if node.key == key {
                node.value = value;
                return;
            }
            entry = &mut node.next;
        }

        *entry = Some(Box::new(HashNode::new(key, value)));
        self.size += 1;
    }

    fn get(&self, key: &str) -> Option<&String> {
        let index = self.hash(key);
        let mut entry = &self.table[index];

        while let Some(ref node) = entry {
            if node.key == key {
                return Some(&node.value);
            }
            entry = &node.next;
        }

        None
    }

    fn remove(&mut self, key: &str) -> Result<(), &'static str> {
    let index = self.hash(key);
    let mut current = &mut self.table[index];
    
    // Ищем узел для удаления
    while let Some(ref mut node) = current {
        if node.key == key {
            // Нашли - заменяем текущий узел на следующий
            *current = node.next.take();
            self.size -= 1;
            return Ok(());
        }
        // Переходим к следующему узлу
        current = &mut current.as_mut().unwrap().next;
    }
    
    // Не нашли ключ
    Err("Key not found!")
}

    fn rehash(&mut self) {
    let old_capacity = self.capacity;
    self.capacity *= 2;
    let mut new_table = vec![None; self.capacity];
    
    for i in 0..old_capacity {
        let mut current = self.table[i].take();
        while let Some(mut node) = current {
            let next = node.next.take();
            let new_index = self.hash(&node.key);
            node.next = new_table[new_index].take();
            new_table[new_index] = Some(node);
            current = next;
        }
    }
    
    self.table = new_table;
}

    fn count(&self) -> usize {
        self.size
    }

    fn print(&self) {
    for bucket in &self.table {
        if let Some(node) = bucket {
            let mut current = node;
            loop {
                println!("{}, {}", current.key, current.value);
                match &current.next {
                    Some(next_node) => current = next_node,
                    None => break,
                };
            }
        }
    }
}

    fn hasher(&self, key: &str, mult: u32, modulus: usize) -> usize {
        let mut hash: u64 = 0;
        for ch in key.chars() {
            hash = hash * mult as u64 + ch as u64;
        }
        (hash % modulus as u64) as usize
    }

    // Сохранение в JSON
    fn save_to_file<P: AsRef<Path>>(&self, filename: P) -> io::Result<()> {
        let file = File::create(filename)?;
        let mut writer = BufWriter::new(file);
    
        // Сериализуем в красивый JSON
        let pretty_json = serde_json::to_string_pretty(&self)?; // Использование to_string_pretty
        writer.write_all(pretty_json.as_bytes())?;
    
        Ok(())
    }

    // Загрузка из JSON с пропуском заголовка
    fn load_from_file<P: AsRef<Path>>(&mut self, filename: P) -> io::Result<()> {
        let file = File::open(filename)?;
        let mut reader = BufReader::new(file);
        
        // Читаем оставшуюся часть (JSON данные)
        let mut json_content = String::new();
        reader.read_to_string(&mut json_content)?;
        
        // Десериализуем JSON
        let loaded_table: HashTable = serde_json::from_str(&json_content)?;
        *self = loaded_table;
        
        Ok(())
    }

    // Сохранение в бинарный файл
    fn save_to_binary_file<P: AsRef<Path>>(&self, filename: P) -> io::Result<()> {
        let file = File::create(filename)?;
        let mut writer = BufWriter::new(file);

        // Сериализуем в бинарный формат
        let encoded: Vec<u8> = serialize(&self).map_err(|e| io::Error::new(io::ErrorKind::Other, e))?;
        writer.write_all(&encoded)?;

        Ok(())
    }

    // Загрузка из бинарного файла
    fn load_from_binary_file<P: AsRef<Path>>(&mut self, filename: P) -> io::Result<()> {
        let file = File::open(filename)?;
        let mut reader = BufReader::new(file);

        // Читаем весь файл
        let mut buffer = Vec::new();
        reader.read_to_end(&mut buffer)?;

        // Десериализуем бинарные данные
        *self = deserialize(&buffer).map_err(|e| io::Error::new(io::ErrorKind::Other, e))?;

        Ok(())
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn insert_get() {
        let mut table = HashTable::new(10);

        assert_eq!(table.get("key1"), None);
        assert_eq!(table.get("key2"), None);
        assert_eq!(table.get("key3"), None);

        table.insert("key1".to_string(), "value1".to_string());
        table.insert("key2".to_string(), "value2".to_string());

        assert_eq!(table.get("key1"), Some(&"value1".to_string()));
        assert_eq!(table.get("key2"), Some(&"value2".to_string()));
        assert_eq!(table.get("key3"), None);

        table.insert("key1".to_string(), "value3".to_string());
        table.insert("key2".to_string(), "value4".to_string());

        assert_eq!(table.get("key1"), Some(&"value3".to_string()));
        assert_eq!(table.get("key2"), Some(&"value4".to_string()));
        assert_eq!(table.get("key3"), None);
        assert_eq!(table.get("key4"), None);
    }

    #[test]
    fn remove() {
        let mut table = HashTable::new(10);

        // Тест удаления несуществующего ключа
        assert_eq!(table.remove("key1"), Err("Key not found!"));

        table.insert("key1".to_string(), "value1".to_string());
        assert_eq!(table.remove("key1"), Ok(()));
        assert_eq!(table.get("key1"), None);
    }

    #[test]
    fn hasher() {
        let table = HashTable::new(2);
        assert_eq!(table.hasher("K1", 31, 2), 0);
    }

    #[test]
    fn hash() {
        let table = HashTable::new(2);
        assert_eq!(table.hash("K1"), 0);
    }

    #[test]
    fn count() {
        let mut table = HashTable::new(10);
        assert_eq!(table.count(), 0);
        
        table.insert("key1".to_string(), "value1".to_string());
        assert_eq!(table.count(), 1);
        
        table.insert("key2".to_string(), "value2".to_string());
        assert_eq!(table.count(), 2);
        
        table.remove("key1").unwrap();
        assert_eq!(table.count(), 1);
    }

#[test]
fn test_print() {
    let mut table = HashTable::new(10);
    table.insert("key1".to_string(), "value1".to_string());
    table.insert("key2".to_string(), "value2".to_string());
    table.print(); // Просто вызываем, чтобы убедиться, что не падает
}

   #[test]
fn overflow_rehash() {
    let mut table = HashTable::new(2);
    
    table.insert("key1".to_string(), "value1".to_string());
    table.insert("key2".to_string(), "value2".to_string());
    table.insert("key3".to_string(), "value3".to_string());
    table.insert("key4".to_string(), "value4".to_string());
    table.insert("key5".to_string(), "value5".to_string());

    // Проверяем что после рехеширования все данные доступны
    assert_eq!(table.get("key1"), Some(&"value1".to_string()));
    assert_eq!(table.get("key2"), Some(&"value2".to_string()));
    assert_eq!(table.get("key3"), Some(&"value3".to_string()));
    assert_eq!(table.get("key4"), Some(&"value4".to_string()));
    assert_eq!(table.get("key5"), Some(&"value5".to_string()));
    
    // Проверяем что емкость увеличилась
    assert_eq!(table.capacity, 4);
}

    #[test]
    fn test_collision_handling() {
        let mut table = HashTable::new(1); // Принудительно создаем коллизии
        
        table.insert("key1".to_string(), "value1".to_string());
        table.insert("key2".to_string(), "value2".to_string());
        table.insert("key3".to_string(), "value3".to_string());

        assert_eq!(table.get("key1"), Some(&"value1".to_string()));
        assert_eq!(table.get("key2"), Some(&"value2".to_string()));
        assert_eq!(table.get("key3"), Some(&"value3".to_string()));

        // Удаление из цепочки
        table.remove("key2").unwrap();
        assert_eq!(table.get("key1"), Some(&"value1".to_string()));
        assert_eq!(table.get("key2"), None);
        assert_eq!(table.get("key3"), Some(&"value3".to_string()));
    }

    #[test]
    fn save_and_load() {
        let mut table1 = HashTable::new(5);
        table1.insert("name".to_string(), "Alice".to_string());
        table1.insert("age".to_string(), "30".to_string());
        table1.insert("city".to_string(), "New York".to_string());

        let original_count = table1.count();
        let original_capacity = table1.capacity;

        table1.save_to_file("file1.data/my_hash.json").unwrap();

        let mut table2 = HashTable::new(5);
        table2.load_from_file("file1.data/my_hash.json").unwrap();

        // Проверяем целостность данных
        assert_eq!(table2.count(), original_count);
        assert_eq!(table2.capacity, original_capacity);
        assert_eq!(table2.get("name"), Some(&"Alice".to_string()));
        assert_eq!(table2.get("age"), Some(&"30".to_string()));
        assert_eq!(table2.get("city"), Some(&"New York".to_string()));

    }

    #[test]
    fn test_multiple_operations() {
        let mut table = HashTable::new(10);
        
        // Множественные операции вставки/удаления
        for i in 0..100 {
            let key = format!("key{}", i);
            let value = format!("value{}", i);
            table.insert(key, value);
        }

        assert_eq!(table.count(), 100);

        // Удаляем каждое второе значение
        for i in 0..100 {
            if i % 2 == 0 {
                let key = format!("key{}", i);
                table.remove(&key).unwrap();
            }
        }

        assert_eq!(table.count(), 50);

        // Проверяем оставшиеся значения
        for i in 0..100 {
            let key = format!("key{}", i);
            if i % 2 == 1 {
                assert_eq!(table.get(&key), Some(&format!("value{}", i)));
            } else {
                assert_eq!(table.get(&key), None);
            }
        }
    }

    #[test]
    fn save_and_load_binary() {
    let mut table1 = HashTable::new(5);
    table1.insert("name".to_string(), "Alice".to_string());
    table1.insert("age".to_string(), "30".to_string());
    table1.insert("city".to_string(), "New York".to_string());
    let original_count = table1.count();
    let original_capacity = table1.capacity;

    table1.save_to_binary_file("file1.data/my_hash.bin").unwrap();
    let mut table2 = HashTable::new(5);
    table2.load_from_binary_file("file1.data/my_hash.bin").unwrap();

    // Проверяем целостность данных
    assert_eq!(table2.count(), original_count);
    assert_eq!(table2.capacity, original_capacity);
    assert_eq!(table2.get("name"), Some(&"Alice".to_string()));
    assert_eq!(table2.get("age"), Some(&"30".to_string()));
    assert_eq!(table2.get("city"), Some(&"New York".to_string()));
}
}

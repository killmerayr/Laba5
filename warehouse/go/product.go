package main

import (
	"fmt"
	"math/rand"
	"strings"
	"time"
)

// Глобальные переменные для склада
var warehouse = make(map[string]map[string]int)
var racks = []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
var sections = []int{1, 2, 3, 4, 5, 6, 7}
var shelves = []int{1, 2, 3, 4}

const MAX_IN_CELL = 10

// Инициализация склада (создание всех ячеек)
func initWarehouse() {
	zone := "A"
	for _, r := range racks {
		for _, s := range sections {
			for _, sh := range shelves {
				address := fmt.Sprintf("%s%02d%d%d", zone, r, s, sh)
				warehouse[address] = make(map[string]int)
			}
		}
	}
}

// Добавление товара в ячейку склада
func addItem(item, address string, count int) {
	cell, ok := warehouse[address]
	if !ok {
		fmt.Printf("Ячейка %s не найдена\n", address)
		return
	}
	total := 0
	for _, quant := range cell {
		total += quant
	}
	if total+count > MAX_IN_CELL {
		fmt.Printf("Нет места в ячейке %s\n", address)
		return
	}
	cell[item] += count
	fmt.Printf("Добавлен %s в ячейку %s\n", item, address)
}

// Удаление товара из ячейки склада
func removeItem(item, address string, count int) {
	cell, ok := warehouse[address]
	if !ok {
		fmt.Printf("Ячейка %s не найдена\n", address)
		return
	}
	quant, ok := cell[item]
	if !ok {
		fmt.Printf("Товар %s не найден\n", item)
		return
	}
	if count <= quant {
		cell[item] -= count
		if cell[item] == 0 {
			delete(cell, item)
		}
		fmt.Printf("Товар %s удален из ячейки %s в количестве %d\n", item, address, count)
	} else {
		fmt.Printf("Число %d больше, чем количество %s\n", count, item)
	}
}

// Информация о складе: загрузка, зоны, содержимое и пустые ячейки
func info() {
	totalCells := len(warehouse)
	totalCapacity := totalCells * MAX_IN_CELL
	totalItems := 0
	zoneItems := make(map[string]int)
	zoneCells := make(map[string]int)
	emptyCells := []string{}

	for address, cell := range warehouse {
		zone := address[:1]
		cellSum := 0
		for _, count := range cell {
			cellSum += count
		}
		totalItems += cellSum
		zoneItems[zone] += cellSum
		zoneCells[zone]++

		if cellSum == 0 {
			emptyCells = append(emptyCells, address)
		} else {
			fmt.Printf("Ячейка %s: ", address)
			for item, count := range cell {
				fmt.Printf("%s (%d) ", item, count)
			}
			fmt.Println()
		}
	}

	if totalCapacity == 0 {
		fmt.Println("Склад пуст, загрузка: 0%")
	} else {
		warehouseLoad := 100.0 * float64(totalItems) / float64(totalCapacity)
		fmt.Printf("Загрузка склада: %.2f%%\n", warehouseLoad)
		for zone, items := range zoneItems {
			zoneCapacity := zoneCells[zone] * MAX_IN_CELL
			var zoneLoad float64
			if zoneCapacity == 0 {
				zoneLoad = 0
			} else {
				zoneLoad = 100.0 * float64(items) / float64(zoneCapacity)
			}
			fmt.Printf("Загрузка зоны %s: %.2f%%\n", zone, zoneLoad)
		}
	}

	fmt.Println("Пустые ячейки:")
	fmt.Println(strings.Join(emptyCells, " "))
}

func main() {
	rand.Seed(time.Now().UnixNano())
	initWarehouse()

	items := []string{"Молоко", "Хлеб", "Яблоко", "Сыр", "Мясо", "Банан", "Яблоко"}

	// Рандомно заполняем склад
	for address := range warehouse {
		if rand.Intn(2) == 0 {
			continue
		}
		item := items[rand.Intn(len(items))]
		count := 1 + rand.Intn(MAX_IN_CELL)
		addItem(item, address, count)
	}

	// Меню пользователя
	for {
		fmt.Print("\nВыберите действие: ADD, REMOVE, INFO, EXIT\n> ")
		var command string
		fmt.Scan(&command)
		switch command {
		case "ADD":
			var item, address string
			var count int
			fmt.Print("Введите товар, адрес и количество: ")
			fmt.Scan(&item, &address, &count)
			addItem(item, address, count)
		case "REMOVE":
			var item, address string
			var count int
			fmt.Print("Введите товар, адрес и количество: ")
			fmt.Scan(&item, &address, &count)
			removeItem(item, address, count)
		case "INFO":
			info()
		case "EXIT":
			return
		default:
			fmt.Println("Неизвестная команда!")
		}
	}
}

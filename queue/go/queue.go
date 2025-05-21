package main

import (
	"fmt"
	"math/rand"
	"sort"
	"time"
)

// Структура для хранения информации о посетителе
type Visitor struct {
	Ticket   string
	Duration int
}

// Функция для генерации номера талона
func generateTicket() string {
	return fmt.Sprintf("T%03d", rand.Intn(900)+100)
}

func main() {
	rand.Seed(time.Now().UnixNano())
	var windowCount int
	fmt.Println(">>> Введите количество окон")
	fmt.Print("<<< ")
	fmt.Scan(&windowCount)

	var visitors []Visitor

	for {
		var command string
		fmt.Scan(&command)
		if command == "ENQUEUE" {
			var duration int
			fmt.Scan(&duration)
			ticket := generateTicket()
			visitors = append(visitors, Visitor{Ticket: ticket, Duration: duration})
			fmt.Println(">>>", ticket)
		} else if command == "DISTRIBUTE" {
			windowTime := make([]int, windowCount)
			windowTickets := make([][]string, windowCount)

			// Сортируем посетителей по убыванию времени
			sortedVisitors := make([]Visitor, len(visitors))
			copy(sortedVisitors, visitors)
			sort.Slice(sortedVisitors, func(i, j int) bool {
				return sortedVisitors[i].Duration > sortedVisitors[j].Duration
			})

			// Распределяем посетителей по окнам (жадно)
			for _, v := range sortedVisitors {
				// Найти окно с минимальным временем
				minIdx := 0
				for i := 1; i < windowCount; i++ {
					if windowTime[i] < windowTime[minIdx] {
						minIdx = i
					}
				}
				windowTime[minIdx] += v.Duration
				windowTickets[minIdx] = append(windowTickets[minIdx], v.Ticket)
			}

			// Выводим результат
			for i, tickets := range windowTickets {
				fmt.Printf(">>> Окно %d (%d минут): ", i+1, windowTime[i])
				for j, ticket := range tickets {
					if j > 0 {
						fmt.Print(", ")
					}
					fmt.Print(ticket)
				}
				fmt.Println()
			}
			break
		} else if command == "EXIT" {
			break
		} else {
			fmt.Println("Неизвестная команда")
		}
	}
}

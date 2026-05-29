use std::io;

// Чтение строки чисел
fn read_numbers() -> Vec<usize> {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    input
        .split_whitespace()
        .map(|x| x.parse::<usize>().unwrap())
        .collect()
}

// Проверка корректности голоса:
// каждый кандидат должен встретиться ровно один раз
fn check_vote(vote: &Vec<usize>, n: usize) -> bool {
    if vote.len() != n {
        return false;
    }

    let mut used = vec![false; n + 1];

    for &candidate in vote {
        if candidate < 1 || candidate > n {
            return false;
        }

        if used[candidate] {
            return false;
        }

        used[candidate] = true;
    }

    true
}

// Метод Борда.
// Возвращает Some(номер кандидата), если победитель один.
// Возвращает None, если победителя нет из-за равенства баллов.
fn find_borda_winner(votes: &Vec<Vec<usize>>, n: usize) -> Option<usize> {
    let mut points = vec![0usize; n + 1];

    for vote in votes {
        for place in 0..n {
            let candidate = vote[place];
            points[candidate] += n - 1 - place;
        }
    }

    println!("\nМетод Борда:");

    for candidate in 1..=n {
        println!("Кандидат {}: {} баллов", candidate, points[candidate]);
    }

    let mut max_points = points[1];

    for candidate in 2..=n {
        if points[candidate] > max_points {
            max_points = points[candidate];
        }
    }

    let mut winners: Vec<usize> = Vec::new();

    for candidate in 1..=n {
        if points[candidate] == max_points {
            winners.push(candidate);
        }
    }

    if winners.len() > 1 {
        print!("Победитель по методу Борда отсутствует: равенство баллов между кандидатами ");

        for candidate in winners {
            print!("{} ", candidate);
        }

        println!();
        return None;
    }

    Some(winners[0])
}

// Проверяет, стоит ли candidate_a выше candidate_b в голосе одного избирателя
fn is_higher(vote: &Vec<usize>, candidate_a: usize, candidate_b: usize) -> bool {
    for &candidate in vote {
        if candidate == candidate_a {
            return true;
        }

        if candidate == candidate_b {
            return false;
        }
    }

    false
}

// Метод Кондорсе.
// Возвращает Some(номер кандидата), если победитель есть.
// Возвращает None, если победителя нет.
fn find_condorcet_winner(votes: &Vec<Vec<usize>>, n: usize) -> Option<usize> {
    for candidate in 1..=n {
        let mut wins_all = true;

        for opponent in 1..=n {
            if candidate == opponent {
                continue;
            }

            let mut candidate_wins = 0usize;
            let mut opponent_wins = 0usize;

            for vote in votes {
                if is_higher(vote, candidate, opponent) {
                    candidate_wins += 1;
                } else {
                    opponent_wins += 1;
                }
            }

            if candidate_wins <= opponent_wins {
                wins_all = false;
                break;
            }
        }

        if wins_all {
            return Some(candidate);
        }
    }

    None
}

fn main() {
    println!("Введите количество кандидатов:");
    let n = read_numbers()[0];

    println!("Введите количество избирателей:");
    let k = read_numbers()[0];

    if n < 2 || k < 1 {
        println!("Ошибка: кандидатов должно быть не меньше 2, избирателей не меньше 1.");
        return;
    }

    let mut votes: Vec<Vec<usize>> = Vec::new();

    println!("\nВведите предпочтения каждого избирателя.");
    println!("Каждая строка - номера кандидатов от лучшего к худшему.");

    for i in 0..k {
        println!("Избиратель {}:", i + 1);

        let vote = read_numbers();

        if !check_vote(&vote, n) {
            println!("Ошибка: некорректное ранжирование у избирателя {}.", i + 1);
            return;
        }

        votes.push(vote);
    }

    match find_borda_winner(&votes, n) {
        Some(winner) => {
            println!("Победитель по методу Борда: кандидат {}", winner);
        }
        None => {}
    }

    println!("\nМетод Кондорсе:");

    match find_condorcet_winner(&votes, n) {
        Some(winner) => {
            println!("Победитель по методу Кондорсе: кандидат {}", winner);
        }
        None => {
            println!("Победитель Кондорсе отсутствует.");
        }
    }
}

use std::io;

fn read_numbers() -> Vec<usize> {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    input
        .split_whitespace()
        .map(|x| x.parse::<usize>().unwrap())
        .collect()
}

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

fn find_borda_winner(votes: &Vec<Vec<usize>>, n: usize) -> usize {
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

    let mut winner = 1;

    for candidate in 2..=n {
        if points[candidate] > points[winner] {
            winner = candidate;
        }
    }

    winner
}

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
    println!("Каждая строка — номера кандидатов от лучшего к худшему.");

    for i in 0..k {
        println!("Избиратель {}:", i + 1);

        let vote = read_numbers();

        if !check_vote(&vote, n) {
            println!("Ошибка: некорректное ранжирование у избирателя {}.", i + 1);
            return;
        }

        votes.push(vote);
    }

    let borda_winner = find_borda_winner(&votes, n);

    println!(
        "Победитель по методу Борда: кандидат {}",
        borda_winner
    );

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

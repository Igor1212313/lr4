const EPS: f64 = 1e-4;

fn f(x: f64) -> f64 {
    x * x + x.exp() - 2.0
}

fn df(x: f64) -> f64 {
    2.0 * x + x.exp()
}

fn phi_negative(x: f64) -> f64 {
    -(2.0 - x.exp()).sqrt()
}

fn phi_positive(x: f64) -> f64 {
    (2.0 - x * x).ln()
}

fn bisection(mut a: f64, mut b: f64) -> f64 {
    let mut n = 0;

    println!("\nМетод половинного деления");
    println!("N\tan\t\tbn\t\tbn - an");

    while (b - a).abs() > EPS {
        println!(
            "{}\t{:.6}\t{:.6}\t{:.6}",
            n,
            a,
            b,
            (b - a).abs()
        );

        let c = (a + b) / 2.0;

        if f(a) * f(c) <= 0.0 {
            b = c;
        } else {
            a = c;
        }

        n += 1;
    }

    println!(
        "{}\t{:.6}\t{:.6}\t{:.6}",
        n,
        a,
        b,
        (b - a).abs()
    );

    (a + b) / 2.0
}

fn newton(mut x0: f64) -> f64 {
    let mut n = 0;

    println!("\nМетод Ньютона");
    println!("N\txn\t\txn+1\t\txn+1 - xn");

    loop {
        let x1 = x0 - f(x0) / df(x0);

        println!(
            "{}\t{:.6}\t{:.6}\t{:.6}",
            n,
            x0,
            x1,
            (x1 - x0).abs()
        );

        x0 = x1;
        n += 1;

        if f(x0).abs() <= EPS {
            break;
        }
    }

    x0
}

fn simple_iteration(mut x0: f64, is_negative_root: bool) -> f64 {
    let mut n = 0;

    println!("\nМетод простых итераций");
    println!("N\txn\t\txn+1\t\txn+1 - xn");

    loop {
        let x1 = if is_negative_root {
            phi_negative(x0)
        } else {
            phi_positive(x0)
        };

        println!(
            "{}\t{:.6}\t{:.6}\t{:.6}",
            n,
            x0,
            x1,
            (x1 - x0).abs()
        );

        x0 = x1;
        n += 1;

        if f(x0).abs() <= EPS {
            break;
        }
    }

    x0
}

fn main() {
    println!("Уравнение: x^2 + e^x = 2");
    println!("f(x) = x^2 + e^x - 2");
    println!("Точность: {:.6}", EPS);

    let intervals = vec![(-2.0, -1.0), (0.0, 1.0)];

    for i in 0..intervals.len() {
        let (a, b) = intervals[i];

        println!("\n====================================");
        println!("Корень {} на отрезке [{:.6}; {:.6}]", i + 1, a, b);

        let root_bisection = bisection(a, b);

        let x0_newton = if i == 1 { a } else { b };
        let root_newton = newton(x0_newton);

        let x0_iter = (a + b) / 2.0;
        let root_iteration = simple_iteration(x0_iter, i == 0);

        println!("\nИтог для корня {}:", i + 1);
        println!("Метод половинного деления: {:.6}", root_bisection);
        println!("Метод Ньютона:             {:.6}", root_newton);
        println!("Метод простых итераций:    {:.6}", root_iteration);
    }

    println!("\nСравнение методов:");
    println!("Метод половинного деления сходится надежно, но медленнее.");
    println!("Метод Ньютона сходится быстрее всего при хорошем начальном приближении.");
    println!("Метод простых итераций проще по формуле, но обычно медленнее метода Ньютона.");
}

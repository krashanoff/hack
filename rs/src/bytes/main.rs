// bytes
//
// Print out the bytes of a file with pretty colors.
// Inspired by https://github.com/sharkdp/hexyl.

use std::fs;
use std::process;
use std::io::{self, Read, Write};
use ansi_term::Color;
use clap::{Arg, App};

fn main() -> io::Result<()> {
    let matches = App::new("bytes")
                    .arg(Arg::with_name("infile")
                            .required(true)
                            .takes_value(true)
                            .value_name("IN")
                            .help("The file to read from")
                    )
                    .author("Leo Krashanoff")
                    .get_matches();

    let in_file: io::Result<fs::File>;

    if let Some(in_path) = matches.value_of("infile") {
        in_file = fs::File::open(in_path);
    } else {
        println!("Please provide a file");
        process::exit(1)
    }

    if let Ok(mut f) = in_file {
        let mut buf = [0; 512];
        let mut iter = 0;
        loop {
            let read = f.read(&mut buf)?;
            if read == 0 {
                break
            }
            
            for c in 0..read {
                io::stdout().write_fmt(format_args!("{:2.x} ", buf[c]))?;
                if c % 16 == 1 {
                    io::stdout().write(b"\n")?;
                    io::stdout().write_fmt(format_args!("{:2}:\t", iter))?;
                    iter += 1;
                }
            }
        }
        io::stdout().write(b"\n")?;
    } else if let Err(e) = in_file {
        println!("{}", e);
        process::exit(1)
    } else {
        println!("No error, weird termination type-beat");
        process::exit(1)
    }

    Ok(())
}
use std::fs;
use std::io::{self, Read, Write};
use clap::{Arg, App};

fn main() {
    let matches = App::new("cat")
                    .version("0.1")
                    .author("Leo Krashanoff")
                    .about("Copy from one file descriptor to another")
                    .arg(Arg::with_name("infile")
                            .required(true)
                            .help("input file")
                            .value_name("IN")
                            .takes_value(true)
                            .index(1)
                        )
                    .arg(Arg::with_name("outfile")
                            .required(true)
                            .help("output file")
                            .value_name("OUT")
                            .takes_value(true)
                            .index(2)
                        )
                    .get_matches();

    let mut in_file = fs::File::open(matches.value_of("infile").expect("Outfile")).expect("Couldn't open infile");
    let mut out_file = fs::File::create(matches.value_of("outfile").expect("Infile")).expect("Couldn't open outfile");

    let mut buf = [0; 256];
    match move || -> io::Result<usize> {
        let mut read;
        loop {
            read = in_file.read(&mut buf)?;
            if read == 0 {
                break
            }
            out_file.write(&buf[..read])?;
        }
        Ok(read)
    }() {
        Ok(_) => println!("Nice!"),
        Err(e) => println!("{}", e)
    }
}

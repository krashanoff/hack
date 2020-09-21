// copypasta
//
// Rust implementation of a pretty meh program
// I wrote in Go.

use clap::{App, Arg};
use std::{
    fs::File,
    io::{self, Read, Seek, SeekFrom, Write},
    process,
    sync::mpsc,
    thread,
};

struct Message {
    pub buf: Box<[u8]>,
    pub loc: u64,
}

fn die(code: i32, msg: &str) -> ! {
    println!("{}", msg);
    process::exit(code)
}

fn main() {
    let matches = App::new("copypasta")
        .arg(
            Arg::with_name("in")
                .required(true)
                .takes_value(true)
                .value_name("INFILE")
                .help("Path to copy from"),
        )
        .arg(
            Arg::with_name("out")
                .required(true)
                .takes_value(true)
                .value_name("OUTFILE")
                .help("Path to copy to"),
        )
        .arg(
            Arg::with_name("verbose")
                .required(false)
                .takes_value(false)
                .short("v")
                .help("Verbose"),
        )
        .get_matches();

    let verbose: bool = matches.is_present("verbose");

    // files
    let mut read_file: File;
    let mut write_file: File;
    if let Ok(rf) = File::open(matches.value_of("in").expect("Input file is required")) {
        read_file = rf;
    } else {
        die(1, "Could not open input file.");
    }
    if let Ok(of) = File::create(matches.value_of("out").expect("Output file is required")) {
        write_file = of;
    } else {
        die(1, "Could not create output file.");
    }

    // channel
    let (send, receive): (mpsc::Sender<Message>, mpsc::Receiver<Message>) = mpsc::channel();

    // spawn writing thread
    let writer = thread::spawn(move || -> io::Result<u64> {
        for msg in receive {
            write_file.seek(SeekFrom::Start(msg.loc))?;
            write_file.write(&*msg.buf)?;
        }
        Ok(0)
    });

    {
        let mut buf = [0; 1000000];
        let mut loc: usize = 0;
        let mut read: usize;
        loop {
            read = read_file.read(&mut buf).unwrap();
            if let Err(e) = send.send(Message {
                loc: loc as u64,
                buf: Box::new(buf),
            }) {
                if verbose {
                    println!("Error writing to location {}: {}.", loc, e);
                }
            } else {
                if read == 0 {
                    break;
                }
                if verbose {
                    println!("Read {} bytes at location {}.", read, loc);
                }
                loc += read;
            }
        }

        drop(send);
    }

    // terminate
    if let Ok(_) = writer.join() {
        if verbose {
            println!("Writer joined successfully!");
        }
    } else {
        die(1, "Writer failed to join.");
    }
}

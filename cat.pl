#!/usr/bin/perl

use strict;

sub cat {
	my $fh = @_[0];
	my $buffer = "x" x 2000;

	while (1) {
		my $n = sysread($fh, $buffer, 2000);
		if (!defined($n)) {
			die "Error reading: $!";
		}

		if ($n == 0) {
			last;
		}

		my $m = syswrite(STDOUT, $buffer, $n);
		if (!defined($m)) {
			die "Error writing: $!";
		}
	}
}

if ($#ARGV < 0) {
	open(my $fh, "<&STDIN") || die "Redirecting stdin: $!";
	cat($fh);
	close($fh) || die "Closing redirected stdin: $!";
} else {
	for (my $i = 0; $i <= $#ARGV; $i++) {
		open(my $fh, "<", $ARGV[$i]) || die "Opening $ARGV[$i]: $!";
		cat($fh);
		close($fh) || die "Closing $ARGV[$i]: $!";
	}
}

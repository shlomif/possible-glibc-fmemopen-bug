#!/usr/bin/perl

use strict;
use warnings;

use Test::More tests => 1;

sub _slurp
{
    my $filename = shift;

    open my $in, '<', $filename
        or die "Cannot open '$filename' for slurping - $!";

    local $/;
    my $contents = <$in>;

    close($in);

    return $contents;
}

{

    # TEST
    is (
        scalar (`./a.out`),
        scalar (_slurp("./good.output.txt")),
        "Good output."
    );
}


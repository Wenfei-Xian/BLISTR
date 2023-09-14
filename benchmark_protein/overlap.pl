#!/usr/bin/perl
use strict;
use warnings;
use List::Util qw(max);

# 存储每个染色体的所有记录
my %chrom_records;

while (<>) {
    chomp;
    my ($chr, $start, $end) = split(/\t/);
    push @{$chrom_records{$chr}}, {start => $start, end => $end, length => $end - $start};
}

# 对每个染色体进行处理
for my $chr (keys %chrom_records) {
    my @records = @{$chrom_records{$chr}};
    
    # 按照起始位置进行排序
    @records = sort {$a->{start} <=> $b->{start}} @records;
    
    my @clusters;
    my $current_cluster = [];
    
    # 分组重叠的记录
    for my $rec (@records) {
        if (@$current_cluster) {
            if ($rec->{start} <= $current_cluster->[-1]{end}) {
                push @$current_cluster, $rec;
            }
            else {
                push @clusters, $current_cluster;
                $current_cluster = [$rec];
            }
        }
        else {
            $current_cluster = [$rec];
        }
    }
    push @clusters, $current_cluster if @$current_cluster;

    # 对每个重叠组，只保留最长的记录
    for my $cluster (@clusters) {
        my $longest = $cluster->[0];
        for my $rec (@$cluster) {
            if ($rec->{length} > $longest->{length}) {
                $longest = $rec;
            }
        }
        print "$chr\t$longest->{start}\t$longest->{end}\n";
    }
}

open IN1,"$ARGV[0]";
$/=">";<IN1>;
while(<IN1>){
	my@lines=split /\n/,$_;
	my$num=@lines;
	if( $num == 2){
		next;
	}
	else{
		my$ID=$lines[0];
		foreach my$line (@lines){
			if($line=~m/Length/){
				my($start,$end)=(split /\s+/,$line)[7,9];
				print "$ID\t$start\t$end\n";
			}
		}
	}
}

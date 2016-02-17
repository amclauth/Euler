#! /usr/bin/perl

use Net::FTP;
use File::Spec;
use File::Find;
use strict;
use warnings;

my $loc = "/www/euler/data/src/java";
my $user = "amclauth";
my $pass = "M4c\@cpanel";
my @validExt = ("java","cpp","h","cl");
my $upload = 1;

my @output = `which highlight`;
if ($output[0] =~ /Command not found/)
{
   die("highlight not installed on this system or not in the path.");
}

open (IN, "gather.txt") or die ("Can't open gathering file.");

if (! -d "./html")
{
   if (!mkdir("html"))
   {
      die ("Can't make html directory.\n");
   }
}

my @in_files = ();

while (my $line = <IN>)
{
   chomp($line);
   push(@in_files,$line);
}

my @absolute = ();
find({
      wanted => sub {push @absolute, $_ if -f and -r },
      no_chdir => 1,},".");
#dedup
@absolute = do {my %h; @h{@absolute} = @absolute; values %h; };

my @out_files = ();

for my $f (@absolute)
{
   my $publishable = 0;
   my $found = 0;
   for my $file (@in_files)
   {
      if ($f =~ /$file$/)
      {
         $found = 1;
         $publishable = 1;
      }
   }
   for my $ext (@validExt)
   {
      if ($f =~ /\.$ext$/i)
      {
         $found = 1;
      }
   }
   if ($found)
   {
      #make highlighted html
      my $out = highlight($f);
      if ($publishable)
      {
         print "publishable";
         #push highlighted html to out files
         push(@out_files,$out);
      }
      print " ::: $f";
      print "\n";
   }
}

if ($upload)
{

   my $ftp = Net::FTP->new("mclauthlin.com", Debug => 0) or
      die("Can't connect to mclauthlin.com: $@\n");

   $ftp->login($user,$pass) or 
      die("Can't log in to mclauthlin.com: " . $ftp->message . "\n");

   $ftp->cwd($loc) or
      die("Can't change working directory: " . $ftp->message . "\n");

   for my $f (@out_files)
   {
      print "Uploading $f: ";
      $ftp->put($f) or
         die("\n\nCan't put $f: " . $ftp->message . "\n");
      print "Done\n";
   }

   $ftp->quit;
}

sub highlight
{
   my $file = shift;
   my $out = $file;
   $out =~ s/^.*\///;
   $out = "html/$out.html";
   my $cmd = "highlight -i $file -o $out --include-style --style=seashell -t 3 --force";
   my @output = `$cmd`;
   for my $line (@output)
   {
      print "$line\n";
   }
   return $out;
}

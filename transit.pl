#!/usr/local/bin/perl
use strict;
use warnings;

my ($FILE,  @paraArr, $filetype);
my $query_string;
my $decode;
my $CONFIG_FILE = "/Library/WebServer/Documents/CONFIG";
my $CSZL_FILE = "/Library/WebServer/Documents/CSZL";
my $SBZL_FILE = "/Library/WebServer/Documents/SBZL";

my $method = $ENV{'REQUEST_METHOD'};

sub URLDecode {
    my $theURL = $_[0];
    chomp($theURL);
    $theURL =~ tr/+/ /;
    $theURL =~ s/%([a-fA-F0-9]{2,2})/chr(hex($1))/eg;
    $theURL =~ s/<!--(.|\n)*-->//g;
    return $theURL;
}

sub getValueFromArray {
    my @Value = @_;
    my $want = $Value[0];
    shift(@Value);
    my $temp;
    foreach $temp (@Value) {
        if ($temp =~ /$want/) {
            $temp =~ s/$want=//;
            return $temp;
        }
    }
}

sub replaceNumInFile {
    my $name = $_[0];
    my $value = $_[1];
    my $filename = $_[2];
    my $line;
    open($FILE, "<", $filename);
    my @data = <$FILE>;
    close $FILE;
    open($FILE, ">", $filename);
    foreach $line (@data) {
        if ($line =~ $name) {
            $line =~ s/"$name": \d+/"$name": $value/;
        }
        print $FILE $line;
    }
    close $FILE;
}

sub replaceStrInFile {
    my $name = $_[0];
    my $value = $_[1];
    my $filename = $_[2];
    my $line;
    open($FILE, "<", $filename);
    my @data = <$FILE>;
    close $FILE;
    open($FILE, ">", $filename);
    foreach $line (@data) {
        if ($line =~ $name) {
            $line =~ s/"$name": ".*"/"$name": "$value"/;
        }
        print $FILE $line;
    }
    close $FILE;
}


if ($method =~ /GET/) {
    $query_string = $ENV{'QUERY_STRING'};
    die;
} else {
    $query_string = <STDIN>;
}

# 处理POST请求
$decode = URLDecode($query_string);
@paraArr = split(/&/, $decode);

$filetype = getValueFromArray("filetype", @paraArr);

if ($filetype =~ "CONFIG") {
    my $CONFIG_SWITCH = getValueFromArray("CONFIG_SWITCH", @paraArr);
    replaceNumInFile("SWITCH", $CONFIG_SWITCH, $CONFIG_FILE);
    my $CONFIG_SERVER = getValueFromArray("CONFIG_SERVER", @paraArr);
    replaceStrInFile("SERVER", $CONFIG_SERVER, $CONFIG_FILE);
    my $CONFIG_USERKEY = getValueFromArray("CONFIG_USERKEY", @paraArr);
    replaceStrInFile("USERKEY", $CONFIG_USERKEY, $CONFIG_FILE);
    my $CONFIG_DIR = getValueFromArray("CONFIG_DIR", @paraArr);
    replaceStrInFile("DIR", $CONFIG_DIR, $CONFIG_FILE);
    my $CONFIG_DataAcquisition = getValueFromArray("CONFIG_DataAcquisition", @paraArr);
    replaceStrInFile("DataAcquisition", $CONFIG_DataAcquisition, $CONFIG_FILE);
}

if ($filetype =~ "CSZL") {
    my $CSZL_SERVICE_CODE = getValueFromArray("CSZL_SERVICE_CODE", @paraArr);
    replaceStrInFile("SERVICE_CODE", $CSZL_SERVICE_CODE, $CSZL_FILE);
    my $CSZL_SERVICE_NAME = getValueFromArray("CSZL_SERVICE_NAME", @paraArr);
    replaceStrInFile("SERVICE_NAME", $CSZL_SERVICE_NAME, $CSZL_FILE);
    my $CSZL_ADDRESS = getValueFromArray("CSZL_ADDRESS", @paraArr);
    replaceStrInFile("ADDRESS", $CSZL_ADDRESS, $CSZL_FILE);
    my $CSZL_BUSINESS_NATURE = getValueFromArray("CSZL_BUSINESS_NATURE", @paraArr);
    replaceStrInFile("BUSINESS_NATURE", $CSZL_BUSINESS_NATURE, $CSZL_FILE);
    my $CSZL_SERVICE_TYPE = getValueFromArray("CSZL_SERVICE_TYPE", @paraArr);
    replaceNumInFile("SERVICE_TYPE", $CSZL_SERVICE_TYPE, $CSZL_FILE);
    my $CSZL_PROVINCE_CODE = getValueFromArray("CSZL_PROVINCE_CODE", @paraArr);
    replaceStrInFile("PROVINCE_CODE", $CSZL_PROVINCE_CODE, $CSZL_FILE);
    my $CSZL_CITY_CODE = getValueFromArray("CSZL_CITY_CODE", @paraArr);
    replaceStrInFile("CITY_CODE", $CSZL_CITY_CODE, $CSZL_FILE);
    my $CSZL_AREA_CODE = getValueFromArray("CSZL_AREA_CODE", @paraArr);
    replaceStrInFile("AREA_CODE", $CSZL_AREA_CODE, $CSZL_FILE);
    my $CSZL_XPOINT = getValueFromArray("CSZL_XPOINT", @paraArr);
    replaceStrInFile("XPOINT", $CSZL_XPOINT, $CSZL_FILE);
    my $CSZL_YPOINT = getValueFromArray("CSZL_YPOINT", @paraArr);
    replaceStrInFile("YPOINT", $CSZL_YPOINT, $CSZL_FILE);
    my $CSZL_TERMINAL_FACTORY_ORGCODE = getValueFromArray("CSZL_TERMINAL_FACTORY_ORGCODE", @paraArr);
    replaceStrInFile("TERMINAL_FACTORY_ORGCODE", $CSZL_TERMINAL_FACTORY_ORGCODE, $CSZL_FILE);
    my $CSZL_CREATE_TIME = getValueFromArray("CSZL_CREATE_TIME", @paraArr);
    replaceStrInFile("CREATE_TIME", $CSZL_CREATE_TIME, $CSZL_FILE);
}

if ($filetype =~ "SBZL") {
}

print "Content-type: text/html\n";
print "Status: 204 No Content", "\n\n";


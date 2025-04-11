int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	try
	{
		soci::sessio sql("postgresql", "dbname=SP-01DB user=IvanovTD06 password=Mvs689101601");
		sql << "CREATE TABLE IF NOT EXISTS test (id SERIAL PRIMARY KEY, value TEXT)";
		sql << "INSERT INTO test (value) VALUES ('Hello World')";

		std::string value;
		sql << "SELECT value FROM test WHERE id = 1", soci::into(value);
		std::cout << "Value: " << value << std::endl;
	}
	catch (soci::soci_error err)
	{
		cout << err.get_error_message();
	}

}

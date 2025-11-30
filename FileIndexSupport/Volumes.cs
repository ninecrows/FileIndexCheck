using MongoDB.Driver;
using MongoDB.Bson;

namespace FileIndexSupport
{
    public class Volumes
    {
        private string ourConnectionString;

        public Volumes(string myConnectionString)
        {
            ourConnectionString = myConnectionString;

            var client = new MongoClient(ourConnectionString);

            var collection = client.GetDatabase("Volumes");

            var collectionBooks = client.GetDatabase("HashIndexOut");
        }
    }
}

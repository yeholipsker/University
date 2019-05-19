namespace Ex3.Migrations
{
    using Ex3.Models;
    using System;
    using System.Data.Entity;
    using System.Data.Entity.Migrations;
    using System.Linq;

    internal sealed class Configuration : DbMigrationsConfiguration<Ex3.Models.Ex3Context>
    {
        public Configuration()
        {
            AutomaticMigrationsEnabled = false;
        }

        protected override void Seed(Ex3.Models.Ex3Context context)
        {
            //  This method will be called after migrating to the latest version.

            //  You can use the DbSet<T>.AddOrUpdate() helper extension method 
            //  to avoid creating duplicate seed data. E.g.
            //
            //    context.People.AddOrUpdate(
            //      p => p.FullName,
            //      new Person { FullName = "Andrew Peters" },
            //      new Person { FullName = "Brice Lambson" },
            //      new Person { FullName = "Rowan Miller" }
            //    );
            //
            context.RegistryModels.AddOrUpdate(
               new RegistryModel { UserName = "noam", Email = "noam@gmail.com", Password = "1234", Wins = 1, Loses = 0 },
           new RegistryModel { UserName = "Yehushoa", Email = "Yehushoa@gmail.com", Password = "1278", Wins = 5, Loses = 4 },
           new RegistryModel { UserName = "no", Email = "no@gmail.com", Password = "6734", Wins = 0, Loses = 4 },
           new RegistryModel { UserName = "Yo", Email = "Yo@gmail.com", Password = "aqws", Wins = 4, Loses = 1 }
           );
        }
    }
}

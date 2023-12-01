using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Clinic.Models;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;

namespace Clinic.Data
{
    public class ClinicDbContext : IdentityDbContext< Users, IdentityRole<int>, int>
    {
        public ClinicDbContext (DbContextOptions<ClinicDbContext> options)
            : base(options)
        {
        }

        public DbSet<Clinic.Models.Patient> Patient { get; set; } = default!;
        public DbSet<Clinic.Models.Doctor> Doctor { get; set; } = default!;
        public DbSet<Clinic.Models.Manager> Manager { get; set; } = default!;
        public DbSet<Clinic.Models.Appointment> Appointment { get; set; } = default!;

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);
        }
    }

}

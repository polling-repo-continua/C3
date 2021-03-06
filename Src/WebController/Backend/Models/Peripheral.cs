﻿using Newtonsoft.Json;
using System;
using FSecure.C3.WebController.Comms;
using System.ComponentModel.DataAnnotations.Schema;
using Newtonsoft.Json.Linq;

namespace FSecure.C3.WebController.Models
{
    public class Peripheral
    {
        [JsonIgnore]
        public ulong AgentId { get; set; }

        [JsonConverter(typeof(HexStringJsonConverter))]
        [JsonProperty("iid")]
        public ulong InterfaceId { get; set; }
        [JsonProperty("type")]
        public ulong Hash { get; set; }
        public string Error { get; set; }

        public JToken Jitter { get; set; }

        [NotMapped]
        public JToken PropertiesText
        {
            get
            {
                return new JObject
                {
                    ["arguments"] = this.StartupCommand?.SelectToken("arguments"),
                    ["jitter"] = this.Jitter,
                };
            }
        }
        public JToken StartupCommand { get; set; }
        public bool ShouldSerializeStartupCommand() => false;

        public bool ShouldSerializeError() => Error != null;
    }
}
